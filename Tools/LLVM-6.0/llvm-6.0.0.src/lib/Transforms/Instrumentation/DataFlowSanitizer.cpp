//===- DataFlowSanitizer.cpp - dynamic data flow analysis -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
/// \file
/// This file is a part of DataFlowSanitizer, a generalised dynamic data flow
/// analysis.
///
/// Unlike other Sanitizer tools, this tool is not designed to detect a specific
/// class of bugs on its own.  Instead, it provides a generic dynamic data flow
/// analysis framework to be used by clients to help detect application-specific
/// issues within their own code.
///
/// The analysis is based on automatic propagation of data flow labels (also
/// known as taint labels) through a program as it performs computation.  Each
/// byte of application memory is backed by two bytes of shadow memory which
/// hold the label.  On Linux/x86_64, memory is laid out as follows:
///
/// +--------------------+ 0x800000000000 (top of memory)
/// | application memory |
/// +--------------------+ 0x700000008000 (kAppAddr)
/// |                    |
/// |       unused       |
/// |                    |
/// +--------------------+ 0x200200000000 (kUnusedAddr)
/// |    union table     |
/// +--------------------+ 0x200000000000 (kUnionTableAddr)
/// |   shadow memory    |
/// +--------------------+ 0x000000010000 (kShadowAddr)
/// | reserved by kernel |
/// +--------------------+ 0x000000000000
///
/// To derive a shadow memory address from an application memory address,
/// bits 44-46 are cleared to bring the address into the range
/// [0x000000008000,0x100000000000).  Then the address is shifted left by 1 to
/// account for the double byte representation of shadow labels and move the
/// address into the shadow memory range.  See the function
/// DataFlowSanitizer::getShadowAddress below.
///
/// For more information, please refer to the design document:
/// http://clang.llvm.org/docs/DataFlowSanitizerDesign.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/None.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"
#include "llvm/Pass.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/SpecialCaseList.h"
#include "llvm/Transforms/Instrumentation.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Local.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>
#define CY_Added 1
#define Option1 false
#define CY_Temp 1
#define V_8 1
#include <fstream>
#include <sstream>
#include "llvm/ADT/StringExtras.h"
#include <iostream>
#include <map>
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/DebugInfo.h"

using namespace llvm;
using namespace std;


#if CY_Temp
  Function *printf_func = NULL;
  GlobalVariable *FmtStr;
  std::vector<Constant*> indices;
#endif

#if CY_Added
  ConstantInt *CYShadow;
#endif
// External symbol to be used when generating the shadow address for
// architectures with multiple VMAs. Instead of using a constant integer
// the runtime will set the external mask based on the VMA range.
static const char *const kDFSanExternShadowPtrMask = "__dfsan_shadow_ptr_mask";

// The -dfsan-preserve-alignment flag controls whether this pass assumes that
// alignment requirements provided by the input IR are correct.  For example,
// if the input IR contains a load with alignment 8, this flag will cause
// the shadow load to have alignment 16.  This flag is disabled by default as
// we have unfortunately encountered too much code (including Clang itself;
// see PR14291) which performs misaligned access.
static cl::opt<bool> ClPreserveAlignment(
    "dfsan-preserve-alignment",
    cl::desc("respect alignment requirements provided by input IR"), cl::Hidden,
    cl::init(false));

// The ABI list files control how shadow parameters are passed. The pass treats
// every function labelled "uninstrumented" in the ABI list file as conforming
// to the "native" (i.e. unsanitized) ABI.  Unless the ABI list contains
// additional annotations for those functions, a call to one of those functions
// will produce a warning message, as the labelling behaviour of the function is
// unknown.  The other supported annotations are "functional" and "discard",
// which are described below under DataFlowSanitizer::WrapperKind.
static cl::list<std::string> ClABIListFiles(
    "dfsan-abilist",
    cl::desc("File listing native ABI functions and how the pass treats them"),
    cl::Hidden);

// Controls whether the pass uses IA_Args or IA_TLS as the ABI for instrumented
// functions (see DataFlowSanitizer::InstrumentedABI below).
static cl::opt<bool> ClArgsABI(
    "dfsan-args-abi",
    cl::desc("Use the argument ABI rather than the TLS ABI"),
    cl::Hidden);

// Controls whether the pass includes or ignores the labels of pointers in load
// instructions.
static cl::opt<bool> ClCombinePointerLabelsOnLoad(
    "dfsan-combine-pointer-labels-on-load",
    cl::desc("Combine the label of the pointer with the label of the data when "
             "loading from memory."),
#if CY_Added
    cl::Hidden, cl::init(false));
#else
    cl::Hidden, cl::init(true));
#endif

// Controls whether the pass includes or ignores the labels of pointers in
// stores instructions.
static cl::opt<bool> ClCombinePointerLabelsOnStore(
    "dfsan-combine-pointer-labels-on-store",
    cl::desc("Combine the label of the pointer with the label of the data when "
             "storing in memory."),
    cl::Hidden, cl::init(false));

static cl::opt<bool> ClDebugNonzeroLabels(
    "dfsan-debug-nonzero-labels",
    cl::desc("Insert calls to __dfsan_nonzero_label on observing a parameter, "
             "load or return with a nonzero label"),
    cl::Hidden);

static StringRef GetGlobalTypeString(const GlobalValue &G) {
  // Types of GlobalVariables are always pointer types.
  Type *GType = G.getValueType();
  // For now we support blacklisting struct types only.
  if (StructType *SGType = dyn_cast<StructType>(GType)) {
    if (!SGType->isLiteral())
      return SGType->getName();
  }
  return "<unknown type>";
}

namespace {

class DFSanABIList {
  std::unique_ptr<SpecialCaseList> SCL;

 public:
  DFSanABIList() = default;

  void set(std::unique_ptr<SpecialCaseList> List) { SCL = std::move(List); }

  /// Returns whether either this function or its source file are listed in the
  /// given category.
  bool isIn(const Function &F, StringRef Category) const {
      //errs() << "ABI List size: \n"; // << SCL->Sections.size() << "\n";
    return isIn(*F.getParent(), Category) ||
           SCL->inSection("dataflow", "fun", F.getName(), Category);
  }

  /// Returns whether this global alias is listed in the given category.
  ///
  /// If GA aliases a function, the alias's name is matched as a function name
  /// would be.  Similarly, aliases of globals are matched like globals.
  bool isIn(const GlobalAlias &GA, StringRef Category) const {
    if (isIn(*GA.getParent(), Category))
      return true;

    if (isa<FunctionType>(GA.getValueType()))
      return SCL->inSection("dataflow", "fun", GA.getName(), Category);

    return SCL->inSection("dataflow", "global", GA.getName(), Category) ||
           SCL->inSection("dataflow", "type", GetGlobalTypeString(GA),
                          Category);
  }

  /// Returns whether this module is listed in the given category.
  bool isIn(const Module &M, StringRef Category) const {
      /*
      if (SCL->inSection("dataflow", "src", M.getModuleIdentifier(), Category))
        errs() << "This module is listed in the given category\n";
      else
        errs() << "This module is not listed in the given category\n";
      */
    return SCL->inSection("dataflow", "src", M.getModuleIdentifier(), Category);
  }
};

#if V_8
/// TransformedFunction is used to express the result of transforming one
/// function type into another.  This struct is immutable.  It holds metadata
/// useful for updating calls of the old function to the new type.
struct TransformedFunction {
  TransformedFunction(FunctionType* OriginalType,
                      FunctionType* TransformedType,
                      std::vector<unsigned> ArgumentIndexMapping)
      : OriginalType(OriginalType),
        TransformedType(TransformedType),
        ArgumentIndexMapping(ArgumentIndexMapping) {}

  // Disallow copies.
  TransformedFunction(const TransformedFunction&) = delete;
  TransformedFunction& operator=(const TransformedFunction&) = delete;

  // Allow moves.
  TransformedFunction(TransformedFunction&&) = default;
  TransformedFunction& operator=(TransformedFunction&&) = default;

  /// Type of the function before the transformation.
  FunctionType* const OriginalType;

  /// Type of the function after the transformation.
  FunctionType* const TransformedType;

  /// Transforming a function may change the position of arguments.  This
  /// member records the mapping from each argument's old position to its new
  /// position.  Argument positions are zero-indexed.  If the transformation
  /// from F to F' made the first argument of F into the third argument of F',
  /// then ArgumentIndexMapping[0] will equal 2.
  const std::vector<unsigned> ArgumentIndexMapping;
};

/// Given function attributes from a call site for the original function,
/// return function attributes appropriate for a call to the transformed
/// function.
AttributeList TransformFunctionAttributes(
    const TransformedFunction& TransformedFunction,
    LLVMContext& Ctx, AttributeList CallSiteAttrs) {
 
  // Construct a vector of AttributeSet for each function argument.
  std::vector<llvm::AttributeSet> ArgumentAttributes(
      TransformedFunction.TransformedType->getNumParams());

  // Copy attributes from the parameter of the original function to the
  // transformed version.  'ArgumentIndexMapping' holds the mapping from
  // old argument position to new.
  for (unsigned i=0, ie = TransformedFunction.ArgumentIndexMapping.size();
       i < ie; ++i) {
    unsigned TransformedIndex = TransformedFunction.ArgumentIndexMapping[i];
    ArgumentAttributes[TransformedIndex] = CallSiteAttrs.getParamAttributes(i);
  }
 
  // Copy annotations on varargs arguments.
  for (unsigned i = TransformedFunction.OriginalType->getNumParams(),
       ie = CallSiteAttrs.getNumAttrSets(); i<ie; ++i) {
    ArgumentAttributes.push_back(CallSiteAttrs.getParamAttributes(i));
  }
 
  return AttributeList::get(
      Ctx,
      CallSiteAttrs.getFnAttributes(),
      CallSiteAttrs.getRetAttributes(),
      llvm::makeArrayRef(ArgumentAttributes));
}
#endif 
class DataFlowSanitizer : public ModulePass {
  friend struct DFSanFunction;
  friend class DFSanVisitor;
#if CY_Added
  //Temporary
  /*
  Function *printf_func = NULL;
  GlobalVariable *FmtStr;
  std::vector<Constant*> indices;
  */

  std::map<std::string, std::set<long long>>L_Target;
  std::map<std::string, std::set<long long>>R_Target;
  std::map<std::string, std::string>Modify_Target;

  DenseMap<Value *, Value *> CY_ValShadowMap;

  void File_Read();
  void Operand_Modify(CmpInst *CI, long long target, std::set<long long> tmp_set, int target_index, DenseMap<Value *, Value *>ValShadowMap);
#endif

  enum {
    ShadowWidth = 16
  };

  /// Which ABI should be used for instrumented functions?
  enum InstrumentedABI {
    /// Argument and return value labels are passed through additional
    /// arguments and by modifying the return type.
    IA_Args,

    /// Argument and return value labels are passed through TLS variables
    /// __dfsan_arg_tls and __dfsan_retval_tls.
    IA_TLS
  };

  /// How should calls to uninstrumented functions be handled?
  enum WrapperKind {
    /// This function is present in an uninstrumented form but we don't know
    /// how it should be handled.  Print a warning and call the function anyway.
    /// Don't label the return value.
    WK_Warning,

    /// This function does not write to (user-accessible) memory, and its return
    /// value is unlabelled.
    WK_Discard,

    /// This function does not write to (user-accessible) memory, and the label
    /// of its return value is the union of the label of its arguments.
    WK_Functional,

    /// Instead of calling the function, a custom wrapper __dfsw_F is called,
    /// where F is the name of the function.  This function may wrap the
    /// original function or provide its own implementation.  This is similar to
    /// the IA_Args ABI, except that IA_Args uses a struct return type to
    /// pass the return value shadow in a register, while WK_Custom uses an
    /// extra pointer argument to return the shadow.  This allows the wrapped
    /// form of the function type to be expressed in C.
    WK_Custom
  };

  Module *Mod;
  LLVMContext *Ctx;
  IntegerType *ShadowTy;
  PointerType *ShadowPtrTy;
  IntegerType *IntptrTy;
  ConstantInt *ZeroShadow;
  ConstantInt *ShadowPtrMask;
  ConstantInt *ShadowPtrMul;
  Constant *ArgTLS;
  Constant *RetvalTLS;
  void *(*GetArgTLSPtr)();
  void *(*GetRetvalTLSPtr)();
  Constant *GetArgTLS;
  Constant *GetRetvalTLS;
  Constant *ExternalShadowMask;
  FunctionType *DFSanUnionFnTy;
  FunctionType *DFSanUnionLoadFnTy;
  FunctionType *DFSanUnimplementedFnTy;
  FunctionType *DFSanSetLabelFnTy;
  FunctionType *DFSanNonzeroLabelFnTy;
  FunctionType *DFSanVarargWrapperFnTy;
  Constant *DFSanUnionFn;
  Constant *DFSanCheckedUnionFn;
  Constant *DFSanUnionLoadFn;
  Constant *DFSanUnimplementedFn;
  Constant *DFSanSetLabelFn;
  Constant *DFSanNonzeroLabelFn;
  Constant *DFSanVarargWrapperFn;
  MDNode *ColdCallWeights;
  DFSanABIList ABIList;
  DenseMap<Value *, Function *> UnwrappedFnMap;
  AttrBuilder ReadOnlyNoneAttrs;
  bool DFSanRuntimeShadowMask = false;

  Value *getShadowAddress(Value *Addr, Instruction *Pos);
  bool isInstrumented(const Function *F);
  bool isInstrumented(const GlobalAlias *GA);
  FunctionType *getArgsFunctionType(FunctionType *T);
  FunctionType *getTrampolineFunctionType(FunctionType *T);
#if V_8
  TransformedFunction getCustomFunctionType(FunctionType *T);
#else
  FunctionType *getCustomFunctionType(FunctionType *T);
#endif
  InstrumentedABI getInstrumentedABI();
  WrapperKind getWrapperKind(Function *F);
  void addGlobalNamePrefix(GlobalValue *GV);
  Function *buildWrapperFunction(Function *F, StringRef NewFName,
                                 GlobalValue::LinkageTypes NewFLink,
                                 FunctionType *NewFT);
  Constant *getOrBuildTrampolineFunction(FunctionType *FT, StringRef FName);

public:
  static char ID;

  DataFlowSanitizer(
      const std::vector<std::string> &ABIListFiles = std::vector<std::string>(),
      void *(*getArgTLS)() = nullptr, void *(*getRetValTLS)() = nullptr);

  bool doInitialization(Module &M) override;
  bool runOnModule(Module &M) override;
};

struct DFSanFunction {
  DataFlowSanitizer &DFS;
  Function *F;
  DominatorTree DT;
  DataFlowSanitizer::InstrumentedABI IA;
  bool IsNativeABI;
  Value *ArgTLSPtr = nullptr;
  Value *RetvalTLSPtr = nullptr;
  AllocaInst *LabelReturnAlloca = nullptr;
  DenseMap<Value *, Value *> ValShadowMap;
  DenseMap<AllocaInst *, AllocaInst *> AllocaShadowMap;
  std::vector<std::pair<PHINode *, PHINode *>> PHIFixups;
  DenseSet<Instruction *> SkipInsts;
  std::vector<Value *> NonZeroChecks;
  bool AvoidNewBlocks;

  struct CachedCombinedShadow {
    BasicBlock *Block;
    Value *Shadow;
  };
  DenseMap<std::pair<Value *, Value *>, CachedCombinedShadow>
      CachedCombinedShadows;
  DenseMap<Value *, std::set<Value *>> ShadowElements;

  DFSanFunction(DataFlowSanitizer &DFS, Function *F, bool IsNativeABI)
      : DFS(DFS), F(F), IA(DFS.getInstrumentedABI()), IsNativeABI(IsNativeABI) {
    DT.recalculate(*F);
    // FIXME: Need to track down the register allocator issue which causes poor
    // performance in pathological cases with large numbers of basic blocks.
    AvoidNewBlocks = F->size() > 1000;
  }

  Value *getArgTLSPtr();
  Value *getArgTLS(unsigned Index, Instruction *Pos);
  Value *getRetvalTLS();
  Value *getShadow(Value *V);
  void setShadow(Instruction *I, Value *Shadow);
  Value *combineShadows(Value *V1, Value *V2, Instruction *Pos);
  Value *combineOperandShadows(Instruction *Inst);
  Value *loadShadow(Value *ShadowAddr, uint64_t Size, uint64_t Align,
                    Instruction *Pos);
  void storeShadow(Value *Addr, uint64_t Size, uint64_t Align, Value *Shadow,
                   Instruction *Pos);
};

class DFSanVisitor : public InstVisitor<DFSanVisitor> {
public:
  DFSanFunction &DFSF;

  DFSanVisitor(DFSanFunction &DFSF) : DFSF(DFSF) {}

  const DataLayout &getDataLayout() const {
    return DFSF.F->getParent()->getDataLayout();
  }

  void visitOperandShadowInst(Instruction &I);
  void visitBinaryOperator(BinaryOperator &BO);
  void visitCastInst(CastInst &CI);
  void visitCmpInst(CmpInst &CI);
  void visitGetElementPtrInst(GetElementPtrInst &GEPI);
  void visitLoadInst(LoadInst &LI);
  void visitStoreInst(StoreInst &SI);
  void visitReturnInst(ReturnInst &RI);
  void visitCallSite(CallSite CS);
  void visitPHINode(PHINode &PN);
  void visitExtractElementInst(ExtractElementInst &I);
  void visitInsertElementInst(InsertElementInst &I);
  void visitShuffleVectorInst(ShuffleVectorInst &I);
  void visitExtractValueInst(ExtractValueInst &I);
  void visitInsertValueInst(InsertValueInst &I);
  void visitAllocaInst(AllocaInst &I);
  void visitSelectInst(SelectInst &I);
  void visitMemSetInst(MemSetInst &I);
  void visitMemTransferInst(MemTransferInst &I);
};

} // end anonymous namespace

char DataFlowSanitizer::ID;

INITIALIZE_PASS(DataFlowSanitizer, "dfsan",
                "DataFlowSanitizer: dynamic data flow analysis.", false, false)

ModulePass *
llvm::createDataFlowSanitizerPass(const std::vector<std::string> &ABIListFiles,
                                  void *(*getArgTLS)(),
                                  void *(*getRetValTLS)()) {
  return new DataFlowSanitizer(ABIListFiles, getArgTLS, getRetValTLS);
}

DataFlowSanitizer::DataFlowSanitizer(
    const std::vector<std::string> &ABIListFiles, void *(*getArgTLS)(),
    void *(*getRetValTLS)())
    : ModulePass(ID), GetArgTLSPtr(getArgTLS), GetRetvalTLSPtr(getRetValTLS) {
  std::vector<std::string> AllABIListFiles(std::move(ABIListFiles));
  AllABIListFiles.insert(AllABIListFiles.end(), ClABIListFiles.begin(),
                         ClABIListFiles.end());
  ABIList.set(SpecialCaseList::createOrDie(AllABIListFiles));
}

FunctionType *DataFlowSanitizer::getArgsFunctionType(FunctionType *T) {
  SmallVector<Type *, 4> ArgTypes(T->param_begin(), T->param_end());
  ArgTypes.append(T->getNumParams(), ShadowTy);
  if (T->isVarArg())
    ArgTypes.push_back(ShadowPtrTy);
  Type *RetType = T->getReturnType();
  if (!RetType->isVoidTy())
    RetType = StructType::get(RetType, ShadowTy);
  return FunctionType::get(RetType, ArgTypes, T->isVarArg());
}

FunctionType *DataFlowSanitizer::getTrampolineFunctionType(FunctionType *T) {
  assert(!T->isVarArg());
  SmallVector<Type *, 4> ArgTypes;
  ArgTypes.push_back(T->getPointerTo());
  ArgTypes.append(T->param_begin(), T->param_end());
  ArgTypes.append(T->getNumParams(), ShadowTy);
  Type *RetType = T->getReturnType();
  if (!RetType->isVoidTy())
    ArgTypes.push_back(ShadowPtrTy);
  return FunctionType::get(T->getReturnType(), ArgTypes, false);
}

#if V_8
TransformedFunction DataFlowSanitizer::getCustomFunctionType(FunctionType *T) {
  SmallVector<Type *, 4> ArgTypes;

  // Some parameters of the custom function being constructed are
  // parameters of T.  Record the mapping from parameters of T to
  // parameters of the custom function, so that parameter attributes
  // at call sites can be updated.
  std::vector<unsigned> ArgumentIndexMapping;
  for (unsigned i = 0, ie = T->getNumParams(); i != ie; ++i) {
    Type* param_type = T->getParamType(i);
    FunctionType *FT;
    if (isa<PointerType>(param_type) && (FT = dyn_cast<FunctionType>(
            cast<PointerType>(param_type)->getElementType()))) {
      ArgumentIndexMapping.push_back(ArgTypes.size());
      ArgTypes.push_back(getTrampolineFunctionType(FT)->getPointerTo());
      ArgTypes.push_back(Type::getInt8PtrTy(*Ctx));
    } else {
      ArgumentIndexMapping.push_back(ArgTypes.size());
      ArgTypes.push_back(param_type);
    }
  }
  for (unsigned i = 0, e = T->getNumParams(); i != e; ++i)
    ArgTypes.push_back(ShadowTy);
  if (T->isVarArg())
    ArgTypes.push_back(ShadowPtrTy);
  Type *RetType = T->getReturnType();
  if (!RetType->isVoidTy()) 
    ArgTypes.push_back(ShadowPtrTy); 
  return TransformedFunction( 
      T, FunctionType::get(T->getReturnType(), ArgTypes, T->isVarArg()), 
      ArgumentIndexMapping); 
}
#else
FunctionType *DataFlowSanitizer::getCustomFunctionType(FunctionType *T) {
  SmallVector<Type *, 4> ArgTypes;
  for (FunctionType::param_iterator i = T->param_begin(), e = T->param_end();
       i != e; ++i) {
    FunctionType *FT;
    if (isa<PointerType>(*i) && (FT = dyn_cast<FunctionType>(cast<PointerType>(
                                     *i)->getElementType()))) {
      ArgTypes.push_back(getTrampolineFunctionType(FT)->getPointerTo());
      ArgTypes.push_back(Type::getInt8PtrTy(*Ctx));
    } else {
      ArgTypes.push_back(*i);
    }
  }
  for (unsigned i = 0, e = T->getNumParams(); i != e; ++i)
    ArgTypes.push_back(ShadowTy);
  if (T->isVarArg())
    ArgTypes.push_back(ShadowPtrTy);
  Type *RetType = T->getReturnType();
  if (!RetType->isVoidTy())
    ArgTypes.push_back(ShadowPtrTy);
  return FunctionType::get(T->getReturnType(), ArgTypes, T->isVarArg());
}
#endif

#if CY_Added
static GlobalVariable* global_string(LLVMContext& ctx, Module *mod, const char *str, const char *name) {
    return new GlobalVariable(
            *mod,
            llvm::ArrayType::get(llvm::IntegerType::get(ctx, 8), strlen(str)+1),
            true,
            llvm::GlobalValue::PrivateLinkage,
            ConstantDataArray::getString(ctx, str),
            name);
}
static Function* printf_prototype(LLVMContext& ctx, Module *mod) {
    std::vector<Type*> printf_arg_types;
    printf_arg_types.push_back(Type::getInt8PtrTy(ctx));

    FunctionType *printf_type = FunctionType::get(Type::getInt32Ty(ctx), printf_arg_types, true);
    Function *func = mod->getFunction("printf");
    if(!func)
        func = Function::Create(printf_type, Function::ExternalLinkage, Twine("printf"), mod);
    func->setCallingConv(CallingConv::C);
    return func;
}

std::string getFile(Instruction* I){

	if (MDNode *N = I->getMetadata("dbg")) { // this if is never executed
		DILocation* Loc = I->getDebugLoc();
		unsigned Line = Loc->getLine();
		std::string str("File:");
		//return Line;
		str = str + Loc->getFilename().data();
		return str;
		//return ConstantInt::get(Type::getInt32Ty(I->getContext()), Line);
	}else {
		return "File:-";
	}
}

std::string getLineNumber(Instruction* I){
	if (MDNode *N = I->getMetadata("dbg")) { // this if is never executed
		DILocation* Loc = I->getDebugLoc();
		unsigned Line = Loc->getLine();
		std::string str("File: ");
		//return Line;
		str = str + Loc->getFilename().data() + " Line: " + std::to_string(Line);
		return str;
		//return ConstantInt::get(Type::getInt32Ty(I->getContext()), Line);
	}else {
		return "File: - Line: - ";
	}
}

void DataFlowSanitizer::File_Read(){
    std::set<int> tmp;
 	string line;
 	ifstream inFile("../NEW_INPUT_v5.txt");
 	//ifstream inFile("NEW_INPUT.txt");
 	while (getline(inFile, line)){
        //errs() << "Original Line: " << line << "\n";
	 	int p0 = line.find("|");
	 	std::string Prefix = line.substr(0, p0);
	 	//errs() << "Prefix: " << Prefix << "\n";

        //Modify_Target[Prefix] = line[p0+1];
        Modify_Target[Prefix] = line.substr(p0+1, line.size()-p0-1);
        errs() << Modify_Target[Prefix] << "\n";
 	}
 	//errs() << "END\n";
	inFile.close();
}

Value* Locate_Variable(Value* Target){
    return NULL;
}

void DataFlowSanitizer::Operand_Modify(CmpInst *CI, long long target, std::set<long long> tmp_set, int target_index, DenseMap<Value *, Value *>ValShadowMap){
        Value *curOperand = CI->getOperand(target_index);
        if (isa<ConstantInt>(curOperand)){
            errs() << "Constant\n";
            return;
        }
        Type *CMPType = curOperand->getType();
        if (!CMPType->isIntOrIntVectorTy())
            return;
        IRBuilder<> builder(CI);
        std::string tmp_str("Label: %u\n");
        assert (ValShadowMap.count(curOperand));
        Value *curTag = ValShadowMap[curOperand];
        errs() << "Ori Value: " << *curOperand << "\n";
        errs() << "Taint Tag: " << *curTag << "\n";
        FmtStr = global_string(*Ctx, Mod, tmp_str.c_str(), "Formate"); //todo
        Constant *var_ref = ConstantExpr::getGetElementPtr(NULL, FmtStr, indices);
        CallInst *call = builder.CreateCall(printf_func, {var_ref, curTag}, "CY_Taint"); //prinf_func
}
#endif
bool DataFlowSanitizer::doInitialization(Module &M) {
  File_Read();
  Triple TargetTriple(M.getTargetTriple());
  bool IsX86_64 = TargetTriple.getArch() == Triple::x86_64;
  bool IsMIPS64 = TargetTriple.getArch() == Triple::mips64 ||
                  TargetTriple.getArch() == Triple::mips64el;
  bool IsAArch64 = TargetTriple.getArch() == Triple::aarch64 ||
                   TargetTriple.getArch() == Triple::aarch64_be;

  const DataLayout &DL = M.getDataLayout();

  Mod = &M;
  Ctx = &M.getContext();
#if CY_Added
  errs() << "Initialization of DataFlowSanitizer\n";
  printf_func = printf_prototype(*Ctx, Mod);
  Constant *zero = Constant::getNullValue(IntegerType::getInt32Ty(*Ctx));
  indices.push_back(zero);
  indices.push_back(zero);
#endif
  ShadowTy = IntegerType::get(*Ctx, ShadowWidth);
  ShadowPtrTy = PointerType::getUnqual(ShadowTy);
  IntptrTy = DL.getIntPtrType(*Ctx);
  ZeroShadow = ConstantInt::getSigned(ShadowTy, 0);
  CYShadow = ConstantInt::getSigned(ShadowTy, 8888);
  ShadowPtrMul = ConstantInt::getSigned(IntptrTy, ShadowWidth / 8);
  if (IsX86_64)
    ShadowPtrMask = ConstantInt::getSigned(IntptrTy, ~0x700000000000LL);
  else if (IsMIPS64)
    ShadowPtrMask = ConstantInt::getSigned(IntptrTy, ~0xF000000000LL);
  // AArch64 supports multiple VMAs and the shadow mask is set at runtime.
  else if (IsAArch64)
    DFSanRuntimeShadowMask = true;
  else
    report_fatal_error("unsupported triple");

  Type *DFSanUnionArgs[2] = { ShadowTy, ShadowTy };
  DFSanUnionFnTy =
      FunctionType::get(ShadowTy, DFSanUnionArgs, /*isVarArg=*/ false);
  Type *DFSanUnionLoadArgs[2] = { ShadowPtrTy, IntptrTy };
  DFSanUnionLoadFnTy =
      FunctionType::get(ShadowTy, DFSanUnionLoadArgs, /*isVarArg=*/ false);
  DFSanUnimplementedFnTy = FunctionType::get(
      Type::getVoidTy(*Ctx), Type::getInt8PtrTy(*Ctx), /*isVarArg=*/false);
  Type *DFSanSetLabelArgs[3] = { ShadowTy, Type::getInt8PtrTy(*Ctx), IntptrTy };
  DFSanSetLabelFnTy = FunctionType::get(Type::getVoidTy(*Ctx),
                                        DFSanSetLabelArgs, /*isVarArg=*/false);
  DFSanNonzeroLabelFnTy = FunctionType::get(
      Type::getVoidTy(*Ctx), None, /*isVarArg=*/false);
  DFSanVarargWrapperFnTy = FunctionType::get(
      Type::getVoidTy(*Ctx), Type::getInt8PtrTy(*Ctx), /*isVarArg=*/false);

  if (GetArgTLSPtr) {
    Type *ArgTLSTy = ArrayType::get(ShadowTy, 64);
    ArgTLS = nullptr;
    GetArgTLS = ConstantExpr::getIntToPtr(
        ConstantInt::get(IntptrTy, uintptr_t(GetArgTLSPtr)),
        PointerType::getUnqual(
            FunctionType::get(PointerType::getUnqual(ArgTLSTy), false)));
  }
  if (GetRetvalTLSPtr) {
    RetvalTLS = nullptr;
    GetRetvalTLS = ConstantExpr::getIntToPtr(
        ConstantInt::get(IntptrTy, uintptr_t(GetRetvalTLSPtr)),
        PointerType::getUnqual(
            FunctionType::get(PointerType::getUnqual(ShadowTy), false)));
  }

  ColdCallWeights = MDBuilder(*Ctx).createBranchWeights(1, 1000);
  return true;
}

bool DataFlowSanitizer::isInstrumented(const Function *F) {
    //errs() << "check is it's instrumented or not\n";
  return !ABIList.isIn(*F, "uninstrumented");
}

bool DataFlowSanitizer::isInstrumented(const GlobalAlias *GA) {
  return !ABIList.isIn(*GA, "uninstrumented");
}

DataFlowSanitizer::InstrumentedABI DataFlowSanitizer::getInstrumentedABI() {
  return ClArgsABI ? IA_Args : IA_TLS;
}

DataFlowSanitizer::WrapperKind DataFlowSanitizer::getWrapperKind(Function *F) {
  if (ABIList.isIn(*F, "functional"))
    return WK_Functional;
  if (ABIList.isIn(*F, "discard"))
    return WK_Discard;
  if (ABIList.isIn(*F, "custom"))
    return WK_Custom;

  return WK_Warning;
}

void DataFlowSanitizer::addGlobalNamePrefix(GlobalValue *GV) {
  std::string GVName = GV->getName(), Prefix = "dfs$";
  GV->setName(Prefix + GVName);

  // Try to change the name of the function in module inline asm.  We only do
  // this for specific asm directives, currently only ".symver", to try to avoid
  // corrupting asm which happens to contain the symbol name as a substring.
  // Note that the substitution for .symver assumes that the versioned symbol
  // also has an instrumented name.
  std::string Asm = GV->getParent()->getModuleInlineAsm();
  std::string SearchStr = ".symver " + GVName + ",";
  size_t Pos = Asm.find(SearchStr);
  if (Pos != std::string::npos) {
    Asm.replace(Pos, SearchStr.size(),
                ".symver " + Prefix + GVName + "," + Prefix);
    GV->getParent()->setModuleInlineAsm(Asm);
  }
}

Function *
DataFlowSanitizer::buildWrapperFunction(Function *F, StringRef NewFName,
                                        GlobalValue::LinkageTypes NewFLink,
                                        FunctionType *NewFT) {
  FunctionType *FT = F->getFunctionType();
  Function *NewF = Function::Create(NewFT, NewFLink, NewFName,
                                    F->getParent());
  NewF->copyAttributesFrom(F);
  NewF->removeAttributes(
      AttributeList::ReturnIndex,
      AttributeFuncs::typeIncompatible(NewFT->getReturnType()));

  //BasicBlock *BB = BasicBlock::Create(*Ctx, "entry", NewF); //TODO
  BasicBlock *BB = BasicBlock::Create(*Ctx, "CY_INST", NewF); //TODO
  if (F->isVarArg()) {
    NewF->removeAttributes(AttributeList::FunctionIndex,
                           AttrBuilder().addAttribute("split-stack"));
    CallInst::Create(DFSanVarargWrapperFn,
                     //IRBuilder<>(BB).CreateGlobalStringPtr(F->getName()), "",
                     IRBuilder<>(BB).CreateGlobalStringPtr(F->getName()), "CY_INST", //TODO
                     BB);
    new UnreachableInst(*Ctx, BB);
  } else {
    std::vector<Value *> Args;
    unsigned n = FT->getNumParams();
    for (Function::arg_iterator ai = NewF->arg_begin(); n != 0; ++ai, --n)
      Args.push_back(&*ai);
    //CallInst *CI = CallInst::Create(F, Args, "", BB);
    CallInst *CI = CallInst::Create(F, Args, "CY_INST", BB);
    if (FT->getReturnType()->isVoidTy())
      ReturnInst::Create(*Ctx, BB); //CY: No Name
    else
      ReturnInst::Create(*Ctx, CI, BB); //CY: No Name
  }

  return NewF;
}

Constant *DataFlowSanitizer::getOrBuildTrampolineFunction(FunctionType *FT,
                                                          StringRef FName) {
  FunctionType *FTT = getTrampolineFunctionType(FT);
  Constant *C = Mod->getOrInsertFunction(FName, FTT);
  Function *F = dyn_cast<Function>(C);
  if (F && F->isDeclaration()) {
    F->setLinkage(GlobalValue::LinkOnceODRLinkage);
    //BasicBlock *BB = BasicBlock::Create(*Ctx, "entry", F);
    BasicBlock *BB = BasicBlock::Create(*Ctx, "CY_INST", F);
    std::vector<Value *> Args;
    Function::arg_iterator AI = F->arg_begin(); ++AI;
    for (unsigned N = FT->getNumParams(); N != 0; ++AI, --N)
      Args.push_back(&*AI);
    //CallInst *CI = CallInst::Create(&*F->arg_begin(), Args, "", BB);
    CallInst *CI = CallInst::Create(&*F->arg_begin(), Args, "CY_INST", BB);
    ReturnInst *RI;
    if (FT->getReturnType()->isVoidTy())
      RI = ReturnInst::Create(*Ctx, BB);
    else
      RI = ReturnInst::Create(*Ctx, CI, BB);

    DFSanFunction DFSF(*this, F, /*IsNativeABI=*/true);
    Function::arg_iterator ValAI = F->arg_begin(), ShadowAI = AI; ++ValAI;
    for (unsigned N = FT->getNumParams(); N != 0; ++ValAI, ++ShadowAI, --N)
      DFSF.ValShadowMap[&*ValAI] = &*ShadowAI;
    DFSanVisitor(DFSF).visitCallInst(*CI);
    if (!FT->getReturnType()->isVoidTy())
      new StoreInst(DFSF.getShadow(RI->getReturnValue()),
                    &*std::prev(F->arg_end()), RI);
  }

  return C;
}

bool DataFlowSanitizer::runOnModule(Module &M) {
    //errs() << "CY: Start\n";
#if CY_Added
    LLVMContext *context = &M.getContext();
#endif
  if (ABIList.isIn(M, "skip"))
    return false;

  //errs() << "End of the DataFlowSanitizer Pass. Size of DFSF: " << DFSF.ValShadowMap.size() << "\n";

  if (!GetArgTLSPtr) {
    Type *ArgTLSTy = ArrayType::get(ShadowTy, 64);
    ArgTLS = Mod->getOrInsertGlobal("__dfsan_arg_tls", ArgTLSTy);
    if (GlobalVariable *G = dyn_cast<GlobalVariable>(ArgTLS))
      G->setThreadLocalMode(GlobalVariable::InitialExecTLSModel);
  }
  if (!GetRetvalTLSPtr) {
    RetvalTLS = Mod->getOrInsertGlobal("__dfsan_retval_tls", ShadowTy);
    if (GlobalVariable *G = dyn_cast<GlobalVariable>(RetvalTLS))
      G->setThreadLocalMode(GlobalVariable::InitialExecTLSModel);
  }

  ExternalShadowMask =
      Mod->getOrInsertGlobal(kDFSanExternShadowPtrMask, IntptrTy);

  DFSanUnionFn = Mod->getOrInsertFunction("__dfsan_union", DFSanUnionFnTy);
  if (Function *F = dyn_cast<Function>(DFSanUnionFn)) {
    F->addAttribute(AttributeList::FunctionIndex, Attribute::NoUnwind);
    F->addAttribute(AttributeList::FunctionIndex, Attribute::ReadNone);
    F->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);
    F->addParamAttr(0, Attribute::ZExt);
    F->addParamAttr(1, Attribute::ZExt);
  }
  DFSanCheckedUnionFn = Mod->getOrInsertFunction("dfsan_union", DFSanUnionFnTy);
  if (Function *F = dyn_cast<Function>(DFSanCheckedUnionFn)) {
    F->addAttribute(AttributeList::FunctionIndex, Attribute::NoUnwind);
    F->addAttribute(AttributeList::FunctionIndex, Attribute::ReadNone);
    F->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);
    F->addParamAttr(0, Attribute::ZExt);
    F->addParamAttr(1, Attribute::ZExt);
  }
  DFSanUnionLoadFn =
      Mod->getOrInsertFunction("__dfsan_union_load", DFSanUnionLoadFnTy);
  if (Function *F = dyn_cast<Function>(DFSanUnionLoadFn)) {
    F->addAttribute(AttributeList::FunctionIndex, Attribute::NoUnwind);
    F->addAttribute(AttributeList::FunctionIndex, Attribute::ReadOnly);
    F->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);
  }
  DFSanUnimplementedFn =
      Mod->getOrInsertFunction("__dfsan_unimplemented", DFSanUnimplementedFnTy);
  DFSanSetLabelFn =
      Mod->getOrInsertFunction("__dfsan_set_label", DFSanSetLabelFnTy);
  if (Function *F = dyn_cast<Function>(DFSanSetLabelFn)) {
    F->addParamAttr(0, Attribute::ZExt);
  }
  DFSanNonzeroLabelFn =
      Mod->getOrInsertFunction("__dfsan_nonzero_label", DFSanNonzeroLabelFnTy);
  DFSanVarargWrapperFn = Mod->getOrInsertFunction("__dfsan_vararg_wrapper",
                                                  DFSanVarargWrapperFnTy);

  std::vector<Function *> FnsToInstrument;
  SmallPtrSet<Function *, 2> FnsWithNativeABI;
  for (Function &i : M) {
    if (!i.isIntrinsic() &&
        &i != DFSanUnionFn &&
        &i != DFSanCheckedUnionFn &&
        &i != DFSanUnionLoadFn &&
        &i != DFSanUnimplementedFn &&
        &i != DFSanSetLabelFn &&
        &i != DFSanNonzeroLabelFn &&
        &i != DFSanVarargWrapperFn)
      FnsToInstrument.push_back(&i);
  }

  // Give function aliases prefixes when necessary, and build wrappers where the
  // instrumentedness is inconsistent.
  for (Module::alias_iterator i = M.alias_begin(), e = M.alias_end(); i != e;) {
    GlobalAlias *GA = &*i;
    ++i;
    // Don't stop on weak.  We assume people aren't playing games with the
    // instrumentedness of overridden weak aliases.
    if (auto F = dyn_cast<Function>(GA->getBaseObject())) {
      bool GAInst = isInstrumented(GA), FInst = isInstrumented(F);
      if (GAInst && FInst) {
        addGlobalNamePrefix(GA);
      } else if (GAInst != FInst) {
        // Non-instrumented alias of an instrumented function, or vice versa.
        // Replace the alias with a native-ABI wrapper of the aliasee.  The pass
        // below will take care of instrumenting it.
        Function *NewF =
            buildWrapperFunction(F, "", GA->getLinkage(), F->getFunctionType());
        GA->replaceAllUsesWith(ConstantExpr::getBitCast(NewF, GA->getType()));
        NewF->takeName(GA);
        GA->eraseFromParent();
        FnsToInstrument.push_back(NewF);
      }
    }
  }

  ReadOnlyNoneAttrs.addAttribute(Attribute::ReadOnly)
      .addAttribute(Attribute::ReadNone);

  errs() << "Start0\n";
  // First, change the ABI of every function in the module.  ABI-listed
  // functions keep their original ABI and get a wrapper function.
  for (std::vector<Function *>::iterator i = FnsToInstrument.begin(),
                                         e = FnsToInstrument.end();
       i != e; ++i) {
    Function &F = **i;
    FunctionType *FT = F.getFunctionType();

    bool IsZeroArgsVoidRet = (FT->getNumParams() == 0 && !FT->isVarArg() &&
                              FT->getReturnType()->isVoidTy());

    //errs() << "Function: " << F << "\n";
    if (isInstrumented(&F)) {
        //errs() << "Is Instrumented\n";
      // Instrumented functions get a 'dfs$' prefix.  This allows us to more
      // easily identify cases of mismatching ABIs.
      if (getInstrumentedABI() == IA_Args && !IsZeroArgsVoidRet) {
        FunctionType *NewFT = getArgsFunctionType(FT);
        Function *NewF = Function::Create(NewFT, F.getLinkage(), "", &M);
        NewF->copyAttributesFrom(&F);
        NewF->removeAttributes(
            AttributeList::ReturnIndex,
            AttributeFuncs::typeIncompatible(NewFT->getReturnType()));
        for (Function::arg_iterator FArg = F.arg_begin(),
                                    NewFArg = NewF->arg_begin(),
                                    FArgEnd = F.arg_end();
             FArg != FArgEnd; ++FArg, ++NewFArg) {
          FArg->replaceAllUsesWith(&*NewFArg);
        }
        NewF->getBasicBlockList().splice(NewF->begin(), F.getBasicBlockList());

        for (Function::user_iterator UI = F.user_begin(), UE = F.user_end();
             UI != UE;) {
          BlockAddress *BA = dyn_cast<BlockAddress>(*UI);
          ++UI;
          if (BA) {
            BA->replaceAllUsesWith(
                BlockAddress::get(NewF, BA->getBasicBlock()));
            delete BA;
          }
        }
        F.replaceAllUsesWith(
            ConstantExpr::getBitCast(NewF, PointerType::getUnqual(FT)));
        NewF->takeName(&F);
        F.eraseFromParent();
        *i = NewF;
        addGlobalNamePrefix(NewF);
        //errs() << "NewF Name 0-1: " << NewF->getName() << "\n";
      } else {
        addGlobalNamePrefix(&F);
        //errs() << "NewF Name 0-2: " << F.getName() << "\n";
      }
    } else if (!IsZeroArgsVoidRet || getWrapperKind(&F) == WK_Custom) {
      // Build a wrapper function for F.  The wrapper simply calls F, and is
      // added to FnsToInstrument so that any instrumentation according to its
      // WrapperKind is done in the second pass below.
      FunctionType *NewFT = getInstrumentedABI() == IA_Args
                                ? getArgsFunctionType(FT)
                                : FT;
      Function *NewF = buildWrapperFunction(
          &F, std::string("dfsw$") + std::string(F.getName()),
          GlobalValue::LinkOnceODRLinkage, NewFT);
      if (getInstrumentedABI() == IA_TLS)
        NewF->removeAttributes(AttributeList::FunctionIndex, ReadOnlyNoneAttrs);
      //errs() << "NewF Name: " << NewF->getName() << "\n";

      Value *WrappedFnCst =
          ConstantExpr::getBitCast(NewF, PointerType::getUnqual(FT));
      F.replaceAllUsesWith(WrappedFnCst);

      UnwrappedFnMap[WrappedFnCst] = &F;
      *i = NewF;

      if (!F.isDeclaration()) {
        // This function is probably defining an interposition of an
        // uninstrumented function and hence needs to keep the original ABI.
        // But any functions it may call need to use the instrumented ABI, so
        // we instrument it in a mode which preserves the original ABI.
        FnsWithNativeABI.insert(&F);

        // This code needs to rebuild the iterators, as they may be invalidated
        // by the push_back, taking care that the new range does not include
        // any functions added by this code.
        size_t N = i - FnsToInstrument.begin(),
               Count = e - FnsToInstrument.begin();
        FnsToInstrument.push_back(&F);
        i = FnsToInstrument.begin() + N;
        e = FnsToInstrument.begin() + Count;
      }
               // Hopefully, nobody will try to indirectly call a vararg
               // function... yet.
    } else if (FT->isVarArg()) {
      UnwrappedFnMap[&F] = &F;
      *i = nullptr;
    }
  }
  //errs() << "NewF Name2: " << NewF->getName() << "\n";

  errs() << "Start\n";
  for (Function *i : FnsToInstrument) {
    if (!i || i->isDeclaration())
      continue;

    removeUnreachableBlocks(*i);

    DFSanFunction DFSF(*this, i, FnsWithNativeABI.count(i));

    // DFSanVisitor may create new basic blocks, which confuses df_iterator.
    // Build a copy of the list before iterating over it.
    SmallVector<BasicBlock *, 4> BBList(depth_first(&i->getEntryBlock()));

    int Offset_Count = 0;
    std::string BB_Name;
    for (BasicBlock *i : BBList) {
      Instruction *Inst = &i->front();
      errs() << "Basic Block: \n";
      errs() << i->getName() << "\n";
      if (i->getName().startswith("b")){
          BB_Name = i->getName();
          Offset_Count = 0;
      }
      else
          Offset_Count--; //Handle extra ReturnInst
      while (true) {
        // DFSanVisitor may split the current basic block, changing the current
        // instruction's next pointer and moving the next instruction to the
        // tail block from which we should continue.

        Offset_Count++;
        if (Inst->getName().startswith("CY_INST"))
            Offset_Count--;
        else if (isa<StoreInst>(Inst) || isa<BranchInst>(Inst)){ //BranchInst & ReturnInst 
            bool temp = false;
            //for (int ind = 0; ind < 2; ind++){
            for (auto operand = Inst->operands().begin(); operand != Inst->operands().end(); operand++){
                if (operand->get() && operand->get()->getName().startswith("CY_INST"))
                    temp = true;
            }
            if (temp)   Offset_Count--;
        }
        Instruction *Next = Inst->getNextNode();
        // DFSanVisitor may delete Inst, so keep track of whether it was a
        // terminator.
        if (LoadInst *LI = dyn_cast<LoadInst>(Inst)){
               /**** Debug ****/

                Value *secondOperand = LI->getPointerOperand();
                if (secondOperand->getName() == "Model0_sysctl_tcp_challenge_ack_limit"){
                    IRBuilder<> builder(LI);
                    //if (DFSF.ValShadowMap.find(secondOperand) != DFSF.ValShadowMap.end() && DFSF.ValShadowMap.find(LI) != DFSF.ValShadowMap.end()){
                    if (!DFSF.ValShadowMap.count(secondOperand)){
                        errs() << "Challenge ACK not existed: " << *secondOperand << "\n";
                    }
                    if (!DFSF.ValShadowMap.count(LI)){
                        errs() << "Instance of Challenge ACK not existed: " << *LI << "\n";
                    }
                    if (DFSF.ValShadowMap.count(secondOperand) && DFSF.ValShadowMap.count(LI)){
                        Value *curTag = DFSF.ValShadowMap[secondOperand];
                        //Value *curTag2 = DFSF.getShadow(secondOperand);
                        Value *LTag = DFSF.ValShadowMap[LI];
                        //Value *LTag2 = DFSF.getShadow(LI);

                        errs() << "CY Ori Value: " << *secondOperand << "\n";
                        errs() << "CY Taint Cur Tag: " << *curTag << "\n";
                        //errs() << "Taint Cur Tag2: " << *curTag2 << "\n";
                        errs() << "Taint Left Tag: " << *LTag << "\n";
                        //errs() << "Taint Left Tag2: " << *LTag2 << "\n";

                        //std::string tmp_str = "CMP ack limit Label: %u, %u with %u, %u\n";
                        std::string tmp_str = "CMP ack limit Label: %u with %u\n";
                        //std::string tmp_str = "CY CMP ack limit Label: %u\n";
                        FmtStr = global_string(*Ctx, Mod, tmp_str.c_str(), "Formate"); //todo
                        Constant *var_ref = ConstantExpr::getGetElementPtr(NULL, FmtStr, indices);
                        //CallInst *call = builder.CreateCall(printf_func, {var_ref, LTag, LTag2, curTag, curTag2}, "CY_Taint"); //prinf_func
                        //CallInst *call = builder.CreateCall(printf_func, {var_ref, LTag2, curTag2}, "CY_Taint3t"); //prinf_func
                        //CallInst *call = builder.CreateCall(printf_func, {var_ref, LTag, curTag}, "CY_Taint3t"); //prinf_func
                        CallInst *call = builder.CreateCall(printf_func, {var_ref, LTag, curTag}, "CY_Taint3t"); //prinf_func
                    }
                    errs() << "End of current Instrumentation\n";
                }
               /**** END ****/


        }
        bool IsTerminator = isa<TerminatorInst>(Inst);
        if (!DFSF.SkipInsts.count(Inst))
          DFSanVisitor(DFSF).visit(Inst);
#if CY_Added
        if (CmpInst *CI = dyn_cast<CmpInst>(Inst)){
            if (CI->getNumOperands() >= 2){
               std::string File_info = getFile(Inst);
               std::string tmp_str = File_info + ","+BB_Name+":"+std::to_string(Offset_Count);

               errs() << tmp_str << "\n"; //CY_NEW_DEBUG
               //if (File_info.find("Model0") != -1 && L_Target.find(tmp_str) != L_Target.end()){ //L_Target and R_Target have same Key
               if (File_info.find("Model0") != -1 && Modify_Target.find(tmp_str) != Modify_Target.end()){ //L_Target and R_Target have same Key
                   errs() << "Matched: " << tmp_str << "\n";
                   std::string target_value = Modify_Target[tmp_str];
                   int target_index = target_value[0]-'0';

                   Value *curOperand = CI->getOperand(target_index);
                   Type *CMPType = curOperand->getType();
                   if (CMPType->isIntOrIntVectorTy()){
                       if (isa<ConstantInt>(curOperand)){
                           errs() << "Constant|" << CI->getParent()->getParent()->getName() << "|" << tmp_str << "|"<<target_value<<"\n";
                       }
                       else{
                           IRBuilder<> builder(CI);
                           target_value = target_value.substr(1, target_value.size()-1);
                           //std::string tmp_str("Label: %u\n");
                           std::string tmp_str("Label: %u" + target_value + "\n");
                           assert (DFSF.ValShadowMap.count(curOperand));
                           Value *curTag = DFSF.ValShadowMap[curOperand];
                           errs() << "Ori Value: " << *curOperand << "\n";
                           errs() << "Taint Tag: " << *curTag << "\n";
                           FmtStr = global_string(*Ctx, Mod, tmp_str.c_str(), "Formate"); //todo
                           Constant *var_ref = ConstantExpr::getGetElementPtr(NULL, FmtStr, indices);
                           CallInst *call = builder.CreateCall(printf_func, {var_ref, curTag}, "CY_Taint"); //prinf_func
                       }
                   }
               }
            }
        }
#endif
        if (IsTerminator){
          break;
        }
        Inst = Next;
      }
    }

    // We will not necessarily be able to compute the shadow for every phi node
    // until we have visited every block.  Therefore, the code that handles phi
    // nodes adds them to the PHIFixups list so that they can be properly
    // handled here.
    for (std::vector<std::pair<PHINode *, PHINode *>>::iterator
             i = DFSF.PHIFixups.begin(),
             e = DFSF.PHIFixups.end();
         i != e; ++i) {
      for (unsigned val = 0, n = i->first->getNumIncomingValues(); val != n;
           ++val) {
        i->second->setIncomingValue(
            val, DFSF.getShadow(i->first->getIncomingValue(val)));
      }
    }

    // -dfsan-debug-nonzero-labels will split the CFG in all kinds of crazy
    // places (i.e. instructions in basic blocks we haven't even begun visiting
    // yet).  To make our life easier, do this work in a pass after the main
    // instrumentation.
    if (ClDebugNonzeroLabels) {
      for (Value *V : DFSF.NonZeroChecks) {
        Instruction *Pos;
        if (Instruction *I = dyn_cast<Instruction>(V))
          Pos = I->getNextNode();
        else
          Pos = &DFSF.F->getEntryBlock().front();
        while (isa<PHINode>(Pos) || isa<AllocaInst>(Pos))
          Pos = Pos->getNextNode();
        IRBuilder<> IRB(Pos);
        Value *Ne = IRB.CreateICmpNE(V, DFSF.DFS.ZeroShadow, "CY_INST");
        BranchInst *BI = cast<BranchInst>(SplitBlockAndInsertIfThen(
            Ne, Pos, /*Unreachable=*/false, ColdCallWeights));
        IRBuilder<> ThenIRB(BI);
        ThenIRB.CreateCall(DFSF.DFS.DFSanNonzeroLabelFn, {}, "CY_INST");
      }
    }
    errs() << "End of the DataFlowSanitizer Pass. Size of DFSF Inside Function: " << DFSF.ValShadowMap.size() << "\n";
    errs() << i->getName() << "\n";
  }

  return false;
}

Value *DFSanFunction::getArgTLSPtr() {
  if (ArgTLSPtr)
    return ArgTLSPtr;
  if (DFS.ArgTLS)
    return ArgTLSPtr = DFS.ArgTLS;

  IRBuilder<> IRB(&F->getEntryBlock().front());
  return ArgTLSPtr = IRB.CreateCall(DFS.GetArgTLS, {}, "CY_INST");
}

Value *DFSanFunction::getRetvalTLS() {
  if (RetvalTLSPtr)
    return RetvalTLSPtr;
  if (DFS.RetvalTLS)
    return RetvalTLSPtr = DFS.RetvalTLS;

  IRBuilder<> IRB(&F->getEntryBlock().front());
  return RetvalTLSPtr = IRB.CreateCall(DFS.GetRetvalTLS, {}, "CY_INST");
}

Value *DFSanFunction::getArgTLS(unsigned Idx, Instruction *Pos) {
  IRBuilder<> IRB(Pos);
  return IRB.CreateConstGEP2_64(getArgTLSPtr(), 0, Idx, "CY_INST");
}

Value *DFSanFunction::getShadow(Value *V) {
  if (!isa<Argument>(V) && !isa<Instruction>(V))
    return DFS.ZeroShadow;
  Value *&Shadow = ValShadowMap[V];
  if (!Shadow) {
      //errs() << "Shadow not exited yet: " << *V << "\n";
    if (Argument *A = dyn_cast<Argument>(V)) {
        //errs() << "Is Argument\n"";
      if (IsNativeABI)
        return DFS.ZeroShadow;
      switch (IA) {
      case DataFlowSanitizer::IA_TLS: {
        Value *ArgTLSPtr = getArgTLSPtr();
        Instruction *ArgTLSPos =
            DFS.ArgTLS ? &*F->getEntryBlock().begin()
                       : cast<Instruction>(ArgTLSPtr)->getNextNode();
        IRBuilder<> IRB(ArgTLSPos);
        Shadow = IRB.CreateLoad(getArgTLS(A->getArgNo(), ArgTLSPos), "CY_INST");
        break;
      }
      case DataFlowSanitizer::IA_Args: {
        unsigned ArgIdx = A->getArgNo() + F->arg_size() / 2;
        Function::arg_iterator i = F->arg_begin();
        while (ArgIdx--)
          ++i;
        Shadow = &*i;
        assert(Shadow->getType() == DFS.ShadowTy);
        break;
      }
      }
      NonZeroChecks.push_back(Shadow);
    } else {
      Shadow = DFS.ZeroShadow;
    }
  }
  return Shadow;
}

void DFSanFunction::setShadow(Instruction *I, Value *Shadow) {
  assert(!ValShadowMap.count(I));
  assert(Shadow->getType() == DFS.ShadowTy);
  ValShadowMap[I] = Shadow;
}

Value *DataFlowSanitizer::getShadowAddress(Value *Addr, Instruction *Pos) {
  //if (Addr == RetvalTLS)
  //    errs() << "RetvalTLS equal to Addr!!!!!!!!\n";
  assert(Addr != RetvalTLS && "Reinstrumenting?");
  IRBuilder<> IRB(Pos);
  Value *ShadowPtrMaskValue;
  if (DFSanRuntimeShadowMask)
    ShadowPtrMaskValue = IRB.CreateLoad(IntptrTy, ExternalShadowMask, "CY_INST");
  else
    ShadowPtrMaskValue = ShadowPtrMask;
  return IRB.CreateIntToPtr(
      IRB.CreateMul(
          IRB.CreateAnd(IRB.CreatePtrToInt(Addr, IntptrTy, "CY_INST"),
                        IRB.CreatePtrToInt(ShadowPtrMaskValue, IntptrTy, "CY_INST"), "CY_INST"),
          ShadowPtrMul, "CY_INST"),
      ShadowPtrTy, "CY_INST");
}

// Generates IR to compute the union of the two given shadows, inserting it
// before Pos.  Returns the computed union Value.
Value *DFSanFunction::combineShadows(Value *V1, Value *V2, Instruction *Pos) {
    //return DFS.CYShadow;
  if (V1 == DFS.ZeroShadow)
    return V2;
  if (V2 == DFS.ZeroShadow)
    return V1;
  if (V1 == V2)
    return V1;

  //return DFS.CYShadow;

  auto V1Elems = ShadowElements.find(V1);
  auto V2Elems = ShadowElements.find(V2);
  if (V1Elems != ShadowElements.end() && V2Elems != ShadowElements.end()) {
    if (std::includes(V1Elems->second.begin(), V1Elems->second.end(),
                      V2Elems->second.begin(), V2Elems->second.end())) {
      return V1;
    } else if (std::includes(V2Elems->second.begin(), V2Elems->second.end(),
                             V1Elems->second.begin(), V1Elems->second.end())) {
      return V2;
    }
  } else if (V1Elems != ShadowElements.end()) {
    if (V1Elems->second.count(V2))
      return V1;
  } else if (V2Elems != ShadowElements.end()) {
    if (V2Elems->second.count(V1))
      return V2;
  }

  auto Key = std::make_pair(V1, V2);
  if (V1 > V2)
    std::swap(Key.first, Key.second);
  CachedCombinedShadow &CCS = CachedCombinedShadows[Key];
  if (CCS.Block && DT.dominates(CCS.Block, Pos->getParent()))
    return CCS.Shadow;

  IRBuilder<> IRB(Pos);
  if (AvoidNewBlocks) {
    CallInst *Call = IRB.CreateCall(DFS.DFSanCheckedUnionFn, {V1, V2}, "CY_INST");
    Call->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);
    Call->addParamAttr(0, Attribute::ZExt);
    Call->addParamAttr(1, Attribute::ZExt);

    CCS.Block = Pos->getParent();
    CCS.Shadow = Call;
  } else {
    BasicBlock *Head = Pos->getParent();
    Value *Ne = IRB.CreateICmpNE(V1, V2, "CY_INST");
    BranchInst *BI = cast<BranchInst>(SplitBlockAndInsertIfThen(
        Ne, Pos, /*Unreachable=*/false, DFS.ColdCallWeights, &DT));
    IRBuilder<> ThenIRB(BI);
    CallInst *Call = ThenIRB.CreateCall(DFS.DFSanUnionFn, {V1, V2}, "CY_INST");
    Call->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);
    Call->addParamAttr(0, Attribute::ZExt);
    Call->addParamAttr(1, Attribute::ZExt);

    BasicBlock *Tail = BI->getSuccessor(0);
    //PHINode *Phi = PHINode::Create(DFS.ShadowTy, 2, "", &Tail->front());
    PHINode *Phi = PHINode::Create(DFS.ShadowTy, 2, "CY_INST", &Tail->front());
    Phi->addIncoming(Call, Call->getParent());
    Phi->addIncoming(V1, Head);

    CCS.Block = Tail;
    CCS.Shadow = Phi;
  }

  std::set<Value *> UnionElems;
  if (V1Elems != ShadowElements.end()) {
    UnionElems = V1Elems->second;
  } else {
    UnionElems.insert(V1);
  }
  if (V2Elems != ShadowElements.end()) {
    UnionElems.insert(V2Elems->second.begin(), V2Elems->second.end());
  } else {
    UnionElems.insert(V2);
  }
  ShadowElements[CCS.Shadow] = std::move(UnionElems);

  return CCS.Shadow;
}

// A convenience function which folds the shadows of each of the operands
// of the provided instruction Inst, inserting the IR before Inst.  Returns
// the computed union Value.
Value *DFSanFunction::combineOperandShadows(Instruction *Inst) {
  if (Inst->getNumOperands() == 0)
    return DFS.ZeroShadow;

  Value *Shadow = getShadow(Inst->getOperand(0));
  for (unsigned i = 1, n = Inst->getNumOperands(); i != n; ++i) {
    Shadow = combineShadows(Shadow, getShadow(Inst->getOperand(i)), Inst);
  }
  return Shadow;
}

void DFSanVisitor::visitOperandShadowInst(Instruction &I) {
  Value *CombinedShadow = DFSF.combineOperandShadows(&I);
  DFSF.setShadow(&I, CombinedShadow);
}

// Generates IR to load shadow corresponding to bytes [Addr, Addr+Size), where
// Addr has alignment Align, and take the union of each of those shadows.
Value *DFSanFunction::loadShadow(Value *Addr, uint64_t Size, uint64_t Align,
                                 Instruction *Pos) {
  if (AllocaInst *AI = dyn_cast<AllocaInst>(Addr)) {
    const auto i = AllocaShadowMap.find(AI);
    if (i != AllocaShadowMap.end()) {
      IRBuilder<> IRB(Pos);
      return IRB.CreateLoad(i->second, "CY_INST");
    }
  }

  uint64_t ShadowAlign = Align * DFS.ShadowWidth / 8;
  SmallVector<Value *, 2> Objs;
  GetUnderlyingObjects(Addr, Objs, Pos->getModule()->getDataLayout());
  bool AllConstants = true;
  for (Value *Obj : Objs) {
    if (isa<Function>(Obj) || isa<BlockAddress>(Obj))
      continue;
    if (isa<GlobalVariable>(Obj) && cast<GlobalVariable>(Obj)->isConstant())
      continue;

    AllConstants = false;
    break;
  }
  if (AllConstants)
    return DFS.ZeroShadow;

  Value *ShadowAddr = DFS.getShadowAddress(Addr, Pos);
  switch (Size) {
  case 0:
    return DFS.ZeroShadow;
  case 1: {
    //LoadInst *LI = new LoadInst(ShadowAddr, "", Pos);
    LoadInst *LI = new LoadInst(ShadowAddr, "CY_INST", Pos);
    LI->setAlignment(ShadowAlign);
    return LI;
  }
  case 2: {
    IRBuilder<> IRB(Pos);
    Value *ShadowAddr1 = IRB.CreateGEP(DFS.ShadowTy, ShadowAddr,
                                       ConstantInt::get(DFS.IntptrTy, 1), "CY_INST");
    return combineShadows(IRB.CreateAlignedLoad(ShadowAddr, ShadowAlign, "CY_INST"),
                          IRB.CreateAlignedLoad(ShadowAddr1, ShadowAlign, "CY_INST"), Pos);
  }
  }
  if (!AvoidNewBlocks && Size % (64 / DFS.ShadowWidth) == 0) {
    // Fast path for the common case where each byte has identical shadow: load
    // shadow 64 bits at a time, fall out to a __dfsan_union_load call if any
    // shadow is non-equal.
    //BasicBlock *FallbackBB = BasicBlock::Create(*DFS.Ctx, "", F);
    BasicBlock *FallbackBB = BasicBlock::Create(*DFS.Ctx, "CY_INST", F);
    IRBuilder<> FallbackIRB(FallbackBB);
    CallInst *FallbackCall = FallbackIRB.CreateCall(
        DFS.DFSanUnionLoadFn,
        {ShadowAddr, ConstantInt::get(DFS.IntptrTy, Size)}, "CY_INST");
    FallbackCall->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);

    // Compare each of the shadows stored in the loaded 64 bits to each other,
    // by computing (WideShadow rotl ShadowWidth) == WideShadow.
    IRBuilder<> IRB(Pos);
    Value *WideAddr =
        IRB.CreateBitCast(ShadowAddr, Type::getInt64PtrTy(*DFS.Ctx), "CY_INST");
    Value *WideShadow = IRB.CreateAlignedLoad(WideAddr, ShadowAlign, "CY_INST");
    Value *TruncShadow = IRB.CreateTrunc(WideShadow, DFS.ShadowTy, "CY_INST");
    Value *ShlShadow = IRB.CreateShl(WideShadow, DFS.ShadowWidth, "CY_INST");
    Value *ShrShadow = IRB.CreateLShr(WideShadow, 64 - DFS.ShadowWidth, "CY_INST");
    Value *RotShadow = IRB.CreateOr(ShlShadow, ShrShadow, "CY_INST");
    Value *ShadowsEq = IRB.CreateICmpEQ(WideShadow, RotShadow, "CY_INST");

    BasicBlock *Head = Pos->getParent();
    BasicBlock *Tail = Head->splitBasicBlock(Pos->getIterator());

    if (DomTreeNode *OldNode = DT.getNode(Head)) {
      std::vector<DomTreeNode *> Children(OldNode->begin(), OldNode->end());

      DomTreeNode *NewNode = DT.addNewBlock(Tail, Head);
      for (auto Child : Children)
        DT.changeImmediateDominator(Child, NewNode);
    }

    // In the following code LastBr will refer to the previous basic block's
    // conditional branch instruction, whose true successor is fixed up to point
    // to the next block during the loop below or to the tail after the final
    // iteration.
    BranchInst *LastBr = BranchInst::Create(FallbackBB, FallbackBB, ShadowsEq); //CY: No Name
    ReplaceInstWithInst(Head->getTerminator(), LastBr);
    DT.addNewBlock(FallbackBB, Head);

    for (uint64_t Ofs = 64 / DFS.ShadowWidth; Ofs != Size;
         Ofs += 64 / DFS.ShadowWidth) {
      //BasicBlock *NextBB = BasicBlock::Create(*DFS.Ctx, "", F);
      BasicBlock *NextBB = BasicBlock::Create(*DFS.Ctx, "CY_INST", F);
      DT.addNewBlock(NextBB, LastBr->getParent());
      IRBuilder<> NextIRB(NextBB);
      WideAddr = NextIRB.CreateGEP(Type::getInt64Ty(*DFS.Ctx), WideAddr,
                                   ConstantInt::get(DFS.IntptrTy, 1), "CY_INST");
      Value *NextWideShadow = NextIRB.CreateAlignedLoad(WideAddr, ShadowAlign, "CY_INST");
      ShadowsEq = NextIRB.CreateICmpEQ(WideShadow, NextWideShadow, "CY_INST");
      LastBr->setSuccessor(0, NextBB);
      LastBr = NextIRB.CreateCondBr(ShadowsEq, FallbackBB, FallbackBB); //CY: No Name
    }

    LastBr->setSuccessor(0, Tail);
    FallbackIRB.CreateBr(Tail); //CY: No Name
    //PHINode *Shadow = PHINode::Create(DFS.ShadowTy, 2, "", &Tail->front());
    PHINode *Shadow = PHINode::Create(DFS.ShadowTy, 2, "CY_INST", &Tail->front());
    Shadow->addIncoming(FallbackCall, FallbackBB);
    Shadow->addIncoming(TruncShadow, LastBr->getParent());
    return Shadow;
  }

  IRBuilder<> IRB(Pos);
  CallInst *FallbackCall = IRB.CreateCall(
      DFS.DFSanUnionLoadFn, {ShadowAddr, ConstantInt::get(DFS.IntptrTy, Size)}, "CY_INST");
  FallbackCall->addAttribute(AttributeList::ReturnIndex, Attribute::ZExt);
  return FallbackCall;
}

void DFSanVisitor::visitLoadInst(LoadInst &LI) {
  auto &DL = LI.getModule()->getDataLayout();
  uint64_t Size = DL.getTypeStoreSize(LI.getType());
  if (Size == 0) {
    DFSF.setShadow(&LI, DFSF.DFS.ZeroShadow);
    return;
  }

  uint64_t Align;
  if (ClPreserveAlignment) {
    Align = LI.getAlignment();
    if (Align == 0)
      Align = DL.getABITypeAlignment(LI.getType());
  } else {
    Align = 1;
  }
  IRBuilder<> IRB(&LI);
  Value *Shadow = DFSF.loadShadow(LI.getPointerOperand(), Size, Align, &LI);
  if (ClCombinePointerLabelsOnLoad) {
    Value *PtrShadow = DFSF.getShadow(LI.getPointerOperand());
    Shadow = DFSF.combineShadows(Shadow, PtrShadow, &LI);
  }
  if (Shadow != DFSF.DFS.ZeroShadow)
    DFSF.NonZeroChecks.push_back(Shadow);

  DFSF.setShadow(&LI, Shadow);
}

void DFSanFunction::storeShadow(Value *Addr, uint64_t Size, uint64_t Align,
                                Value *Shadow, Instruction *Pos) {
  if (AllocaInst *AI = dyn_cast<AllocaInst>(Addr)) {
    const auto i = AllocaShadowMap.find(AI);
    if (i != AllocaShadowMap.end()) {
      IRBuilder<> IRB(Pos);
      IRB.CreateStore(Shadow, i->second); //CY: No Name
      return;
    }
  }

  uint64_t ShadowAlign = Align * DFS.ShadowWidth / 8;
  IRBuilder<> IRB(Pos);
  Value *ShadowAddr = DFS.getShadowAddress(Addr, Pos);
  if (Shadow == DFS.ZeroShadow) {
    IntegerType *ShadowTy = IntegerType::get(*DFS.Ctx, Size * DFS.ShadowWidth);
    Value *ExtZeroShadow = ConstantInt::get(ShadowTy, 0);
    Value *ExtShadowAddr =
        IRB.CreateBitCast(ShadowAddr, PointerType::getUnqual(ShadowTy), "CY_INST");
    IRB.CreateAlignedStore(ExtZeroShadow, ExtShadowAddr, ShadowAlign); //CY: No Name
    return;
  }

  const unsigned ShadowVecSize = 128 / DFS.ShadowWidth;
  uint64_t Offset = 0;
  if (Size >= ShadowVecSize) {
    VectorType *ShadowVecTy = VectorType::get(DFS.ShadowTy, ShadowVecSize);
    Value *ShadowVec = UndefValue::get(ShadowVecTy);
    for (unsigned i = 0; i != ShadowVecSize; ++i) {
      ShadowVec = IRB.CreateInsertElement(
          ShadowVec, Shadow, ConstantInt::get(Type::getInt32Ty(*DFS.Ctx), i), "CY_INST");
    }
    Value *ShadowVecAddr =
        IRB.CreateBitCast(ShadowAddr, PointerType::getUnqual(ShadowVecTy), "CY_INST");
    do {
      Value *CurShadowVecAddr =
          IRB.CreateConstGEP1_32(ShadowVecTy, ShadowVecAddr, Offset, "CY_INST");
      IRB.CreateAlignedStore(ShadowVec, CurShadowVecAddr, ShadowAlign); //CY: No Name
      Size -= ShadowVecSize;
      ++Offset;
    } while (Size >= ShadowVecSize);
    Offset *= ShadowVecSize;
  }
  while (Size > 0) {
    Value *CurShadowAddr =
        IRB.CreateConstGEP1_32(DFS.ShadowTy, ShadowAddr, Offset, "CY_INST");
    IRB.CreateAlignedStore(Shadow, CurShadowAddr, ShadowAlign); //CY: No Name
    --Size;
    ++Offset;
  }
}

void DFSanVisitor::visitStoreInst(StoreInst &SI) {
  auto &DL = SI.getModule()->getDataLayout();
  uint64_t Size = DL.getTypeStoreSize(SI.getValueOperand()->getType());
  if (Size == 0)
    return;

  uint64_t Align;
  if (ClPreserveAlignment) {
    Align = SI.getAlignment();
    if (Align == 0)
      Align = DL.getABITypeAlignment(SI.getValueOperand()->getType());
  } else {
    Align = 1;
  }

  Value* Shadow = DFSF.getShadow(SI.getValueOperand());
  if (SI.getPointerOperand()->getName() == "cy_tmp" || SI.getPointerOperand()->getName() == "cy_tmp2"){
      errs() << "Reach cy_tmp\n";
      if (ClCombinePointerLabelsOnStore)
          errs() << "ClCombinePointerLabelsOnStore is on\n";
      else
          errs() << "ClCombinePointerLabelsOnStore is not on\n";
      errs() << "Shadow: " << *Shadow << "\n";
        
      IRBuilder<> builder(&SI);
      std::string tmp_str = "cy_tmp Label: %u\n";
      //std::string tmp_str = "CY CMP ack limit Label: %u\n";
      errs() << *printf_func << "\n";
      printf_func = printf_prototype(*(DFSF.DFS.Ctx), DFSF.DFS.Mod);
      FmtStr = global_string(*(DFSF.DFS.Ctx), DFSF.DFS.Mod, tmp_str.c_str(), "Formate"); //todo
      Constant *var_ref = ConstantExpr::getGetElementPtr(NULL, FmtStr, indices);
      CallInst *call = builder.CreateCall(printf_func, {var_ref, Shadow}, "CY_Taint"); //prinf_func
  }
  if (ClCombinePointerLabelsOnStore) {
    Value *PtrShadow = DFSF.getShadow(SI.getPointerOperand());
    Shadow = DFSF.combineShadows(Shadow, PtrShadow, &SI);
  }
  DFSF.storeShadow(SI.getPointerOperand(), Size, Align, Shadow, &SI);
}

void DFSanVisitor::visitBinaryOperator(BinaryOperator &BO) {
#if CY_Added
  DFSF.setShadow(&BO, CYShadow);
#else
  visitOperandShadowInst(BO);
#endif
}

void DFSanVisitor::visitCastInst(CastInst &CI) { visitOperandShadowInst(CI); }

void DFSanVisitor::visitCmpInst(CmpInst &CI) { visitOperandShadowInst(CI); }

void DFSanVisitor::visitGetElementPtrInst(GetElementPtrInst &GEPI) {
  visitOperandShadowInst(GEPI);
}

void DFSanVisitor::visitExtractElementInst(ExtractElementInst &I) {
  visitOperandShadowInst(I);
}

void DFSanVisitor::visitInsertElementInst(InsertElementInst &I) {
  visitOperandShadowInst(I);
}

void DFSanVisitor::visitShuffleVectorInst(ShuffleVectorInst &I) {
  visitOperandShadowInst(I);
}

void DFSanVisitor::visitExtractValueInst(ExtractValueInst &I) {
  visitOperandShadowInst(I);
}

void DFSanVisitor::visitInsertValueInst(InsertValueInst &I) {
  visitOperandShadowInst(I);
}

void DFSanVisitor::visitAllocaInst(AllocaInst &I) {
  bool AllLoadsStores = true;
  for (User *U : I.users()) {
    if (isa<LoadInst>(U))
      continue;

    if (StoreInst *SI = dyn_cast<StoreInst>(U)) {
      if (SI->getPointerOperand() == &I)
        continue;
    }

    AllLoadsStores = false;
    break;
  }
  if (AllLoadsStores) {
    IRBuilder<> IRB(&I);
#if CY_Added
    DFSF.AllocaShadowMap[&I] = IRB.CreateAlloca(DFSF.DFS.ShadowTy, nullptr,  "CY_INST"); //
#else
    DFSF.AllocaShadowMap[&I] = IRB.CreateAlloca(DFSF.DFS.ShadowTy); 
#endif
  }
  DFSF.setShadow(&I, DFSF.DFS.ZeroShadow);
}

void DFSanVisitor::visitSelectInst(SelectInst &I) {
  Value *CondShadow = DFSF.getShadow(I.getCondition());
  Value *TrueShadow = DFSF.getShadow(I.getTrueValue());
  Value *FalseShadow = DFSF.getShadow(I.getFalseValue());

  if (isa<VectorType>(I.getCondition()->getType())) {
    DFSF.setShadow(
        &I,
        DFSF.combineShadows(
            CondShadow, DFSF.combineShadows(TrueShadow, FalseShadow, &I), &I));
  } else {
    Value *ShadowSel;
    if (TrueShadow == FalseShadow) {
      ShadowSel = TrueShadow;
    } else {
      ShadowSel =
#if CY_Added
          SelectInst::Create(I.getCondition(), TrueShadow, FalseShadow, "CY_INST", &I);
#else
          SelectInst::Create(I.getCondition(), TrueShadow, FalseShadow, "", &I);
#endif
    }
    DFSF.setShadow(&I, DFSF.combineShadows(CondShadow, ShadowSel, &I));
  }
}

void DFSanVisitor::visitMemSetInst(MemSetInst &I) {
  IRBuilder<> IRB(&I);
  Value *ValShadow = DFSF.getShadow(I.getValue());
#if CY_Added
  IRB.CreateCall(DFSF.DFS.DFSanSetLabelFn,
                 {ValShadow, IRB.CreateBitCast(I.getDest(), Type::getInt8PtrTy(
                                                                *DFSF.DFS.Ctx), "CY_INST"),
                  IRB.CreateZExtOrTrunc(I.getLength(), DFSF.DFS.IntptrTy, "CY_INST")}, "CY_INST");
#else
  IRB.CreateCall(DFSF.DFS.DFSanSetLabelFn,
                 {ValShadow, IRB.CreateBitCast(I.getDest(), Type::getInt8PtrTy(
                                                                *DFSF.DFS.Ctx)),
                  IRB.CreateZExtOrTrunc(I.getLength(), DFSF.DFS.IntptrTy)});
#endif
}

void DFSanVisitor::visitMemTransferInst(MemTransferInst &I) {
  IRBuilder<> IRB(&I);
  Value *DestShadow = DFSF.DFS.getShadowAddress(I.getDest(), &I);
  Value *SrcShadow = DFSF.DFS.getShadowAddress(I.getSource(), &I);
#if CY_Added
  Value *LenShadow = IRB.CreateMul(
      I.getLength(),
      ConstantInt::get(I.getLength()->getType(), DFSF.DFS.ShadowWidth / 8), "CY_INST");
#else
  Value *LenShadow = IRB.CreateMul(
      I.getLength(),
      ConstantInt::get(I.getLength()->getType(), DFSF.DFS.ShadowWidth / 8));
#endif
  Value *AlignShadow;
  if (ClPreserveAlignment) {
#if CY_Added
    AlignShadow = IRB.CreateMul(I.getAlignmentCst(),
                                ConstantInt::get(I.getAlignmentCst()->getType(),
                                                 DFSF.DFS.ShadowWidth / 8), "CY_INST");
#else
    AlignShadow = IRB.CreateMul(I.getAlignmentCst(),
                                ConstantInt::get(I.getAlignmentCst()->getType(),
                                                 DFSF.DFS.ShadowWidth / 8));
#endif
  } else {
    AlignShadow = ConstantInt::get(I.getAlignmentCst()->getType(),
                                   DFSF.DFS.ShadowWidth / 8);
  }
  Type *Int8Ptr = Type::getInt8PtrTy(*DFSF.DFS.Ctx);
  DestShadow = IRB.CreateBitCast(DestShadow, Int8Ptr, "CY_INST");
  SrcShadow = IRB.CreateBitCast(SrcShadow, Int8Ptr, "CY_INST");
  IRB.CreateCall(I.getCalledValue(), {DestShadow, SrcShadow, LenShadow,
                                      AlignShadow, I.getVolatileCst()}, "CY_INST");
}

void DFSanVisitor::visitReturnInst(ReturnInst &RI) {
  if (!DFSF.IsNativeABI && RI.getReturnValue()) {
    switch (DFSF.IA) {
    case DataFlowSanitizer::IA_TLS: {
      Value *S = DFSF.getShadow(RI.getReturnValue());
      IRBuilder<> IRB(&RI);
      IRB.CreateStore(S, DFSF.getRetvalTLS()); //CY: No Name
      break;
    }
    case DataFlowSanitizer::IA_Args: {
      IRBuilder<> IRB(&RI);
      Type *RT = DFSF.F->getFunctionType()->getReturnType();
      Value *InsVal =
          IRB.CreateInsertValue(UndefValue::get(RT), RI.getReturnValue(), 0, "CY_INST");
      Value *InsShadow =
          IRB.CreateInsertValue(InsVal, DFSF.getShadow(RI.getReturnValue()), 1, "CY_INST");
      RI.setOperand(0, InsShadow);
      break;
    }
    }
  }
}


void DFSanVisitor::visitCallSite(CallSite CS) {
  Function *F = CS.getCalledFunction();
  if ((F && F->isIntrinsic()) || isa<InlineAsm>(CS.getCalledValue())) {
    visitOperandShadowInst(*CS.getInstruction());
    return;
  }

  // Calls to this function are synthesized in wrappers, and we shouldn't
  // instrument them.
  if (F == DFSF.DFS.DFSanVarargWrapperFn)
    return;

  IRBuilder<> IRB(CS.getInstruction());

  DenseMap<Value *, Function *>::iterator i =
      DFSF.DFS.UnwrappedFnMap.find(CS.getCalledValue());
  if (i != DFSF.DFS.UnwrappedFnMap.end()) {
    Function *F = i->second;
    switch (DFSF.DFS.getWrapperKind(F)) {
    case DataFlowSanitizer::WK_Warning:
      CS.setCalledFunction(F);
      IRB.CreateCall(DFSF.DFS.DFSanUnimplementedFn,
                     IRB.CreateGlobalStringPtr(F->getName(), "CY_INST10_"), "CY_INST11_");
      DFSF.setShadow(CS.getInstruction(), DFSF.DFS.ZeroShadow);
      return;
    case DataFlowSanitizer::WK_Discard:
      CS.setCalledFunction(F);
      DFSF.setShadow(CS.getInstruction(), DFSF.DFS.ZeroShadow);
      return;
    case DataFlowSanitizer::WK_Functional:
      CS.setCalledFunction(F);
      visitOperandShadowInst(*CS.getInstruction());
      return;
    case DataFlowSanitizer::WK_Custom:
      // Don't try to handle invokes of custom functions, it's too complicated.
      // Instead, invoke the dfsw$ wrapper, which will in turn call the __dfsw_
      // wrapper.
      if (CallInst *CI = dyn_cast<CallInst>(CS.getInstruction())) {
        FunctionType *FT = F->getFunctionType();
#if V_8
        TransformedFunction CustomFn = DFSF.DFS.getCustomFunctionType(FT);
#else
        FunctionType *CustomFT = DFSF.DFS.getCustomFunctionType(FT);
#endif
        std::string CustomFName = "__dfsw_";
        CustomFName += F->getName();
#if CY_Added
        bool TempFix = false;
        if (CustomFName == "__dfsw_sprintf")
            TempFix = true;
#endif

        Constant *CustomF =
#if V_8
            DFSF.DFS.Mod->getOrInsertFunction(CustomFName, CustomFn.TransformedType);
#else
            DFSF.DFS.Mod->getOrInsertFunction(CustomFName, CustomFT);
#endif
        if (Function *CustomFn = dyn_cast<Function>(CustomF)) {
          CustomFn->copyAttributesFrom(F);

          // Custom functions returning non-void will write to the return label.
          if (!FT->getReturnType()->isVoidTy()) {
            CustomFn->removeAttributes(AttributeList::FunctionIndex,
                                       DFSF.DFS.ReadOnlyNoneAttrs);
          }
        }

        errs() << "Getinto __dfsw_sprintf\n";
        std::vector<Value *> Args;

        CallSite::arg_iterator i = CS.arg_begin();
        for (unsigned n = FT->getNumParams(); n != 0; ++i, --n) {
          Type *T = (*i)->getType();
          FunctionType *ParamFT;
          if (isa<PointerType>(T) &&
              (ParamFT = dyn_cast<FunctionType>(
                   cast<PointerType>(T)->getElementType()))) {
            std::string TName = "dfst";
            TName += utostr(FT->getNumParams() - n);
            TName += "$";
            TName += F->getName();
            Constant *T = DFSF.DFS.getOrBuildTrampolineFunction(ParamFT, TName);
            Args.push_back(T);
            Args.push_back(
                IRB.CreateBitCast(*i, Type::getInt8PtrTy(*DFSF.DFS.Ctx), "CY_INST"));
          } else {
            Args.push_back(*i);
          }
        }

        i = CS.arg_begin();
        const unsigned ShadowArgStart = Args.size();
        for (unsigned n = FT->getNumParams(); n != 0; ++i, --n){
          Args.push_back(DFSF.getShadow(*i));
        }

        if (FT->isVarArg()) {
          auto *LabelVATy = ArrayType::get(DFSF.DFS.ShadowTy,
                                           CS.arg_size() - FT->getNumParams());
          auto *LabelVAAlloca = new AllocaInst(
              LabelVATy, getDataLayout().getAllocaAddrSpace(),
              "labelva", &DFSF.F->getEntryBlock().front());

          for (unsigned n = 0; i != CS.arg_end(); ++i, ++n) {
            auto LabelVAPtr = IRB.CreateStructGEP(LabelVATy, LabelVAAlloca, n, "CY_INST");
            IRB.CreateStore(DFSF.getShadow(*i), LabelVAPtr); //CY: No Name
          }

          Args.push_back(IRB.CreateStructGEP(LabelVATy, LabelVAAlloca, 0, "CY_INST_GEP"));
        }

        if (!FT->getReturnType()->isVoidTy()) {
          if (!DFSF.LabelReturnAlloca) {
            DFSF.LabelReturnAlloca =
              new AllocaInst(DFSF.DFS.ShadowTy,
                             getDataLayout().getAllocaAddrSpace(),
                             "labelreturn", &DFSF.F->getEntryBlock().front());
          }
          Args.push_back(DFSF.LabelReturnAlloca);
        }

        for (i = CS.arg_begin() + FT->getNumParams(); i != CS.arg_end(); ++i){
          Args.push_back(*i);
        }

        CallInst *CustomCI = IRB.CreateCall(CustomF, Args, "CY_INST");
        CustomCI->setCallingConv(CI->getCallingConv());
        errs() << "Original CI: " << *CI << "\n";
        /*
        AttributeList AL = CI->getAttributes();
        AttributeSet AS;
        unsigned x = 2;
        AL.dump();
        if (AL.hasAttribute(x)){
            AS = AL.getAttributes(x);
            errs() << "AL has third attribute; Index is for the number of elements\n";
            AS.dump();
        }
        x = 3;
        if (AL.hasAttribute(x)){
            AS = AL.getAttributes(x);
            errs() << "3-nonnull attribute exists;\n";
            AS.dump();

        }
        if (AL.hasParamAttr(x)){
            errs() << "Para 3rd exists\n";
        }
        //errs() << "Attributes: " << (CI->getAttributes()) << "\n";
        errs() << "CallingConv: " << (CI->getCallingConv()) << "\n";
        */
#if CY_Added
        if (!TempFix)
            CustomCI->setAttributes(CI->getAttributes());
#else
        CustomCI->setAttributes(CI->getAttributes());
#endif

        errs() << *CustomCI << "\n";
        errs() << "End phase 6\n";

        // Update the parameter attributes of the custom call instruction to
        // zero extend the shadow parameters. This is required for targets
        // which consider ShadowTy an illegal type.
        for (unsigned n = 0; n < FT->getNumParams(); n++) {
          const unsigned ArgNo = ShadowArgStart + n;
          if (CustomCI->getArgOperand(ArgNo)->getType() == DFSF.DFS.ShadowTy)
            CustomCI->addParamAttr(ArgNo, Attribute::ZExt);
        }

        if (!FT->getReturnType()->isVoidTy()) {
          LoadInst *LabelLoad = IRB.CreateLoad(DFSF.LabelReturnAlloca, "CY_INST");
          DFSF.setShadow(CustomCI, LabelLoad);
        }

        CI->replaceAllUsesWith(CustomCI);
        CI->eraseFromParent();
        return;
      }
      break;
    }
  }

  FunctionType *FT = cast<FunctionType>(
      CS.getCalledValue()->getType()->getPointerElementType());
  if (DFSF.DFS.getInstrumentedABI() == DataFlowSanitizer::IA_TLS) {
    for (unsigned i = 0, n = FT->getNumParams(); i != n; ++i) {
      IRB.CreateStore(DFSF.getShadow(CS.getArgument(i)),
                      DFSF.getArgTLS(i, CS.getInstruction())); //CY: No Name
    }
  }

  Instruction *Next = nullptr;
  if (!CS.getType()->isVoidTy()) {
    if (InvokeInst *II = dyn_cast<InvokeInst>(CS.getInstruction())) {
      if (II->getNormalDest()->getSinglePredecessor()) {
        Next = &II->getNormalDest()->front();
      } else {
        BasicBlock *NewBB =
            SplitEdge(II->getParent(), II->getNormalDest(), &DFSF.DT);
        Next = &NewBB->front();
      }
    } else {
      assert(CS->getIterator() != CS->getParent()->end());
      Next = CS->getNextNode();
    }

    if (DFSF.DFS.getInstrumentedABI() == DataFlowSanitizer::IA_TLS) {
      IRBuilder<> NextIRB(Next);
      LoadInst *LI = NextIRB.CreateLoad(DFSF.getRetvalTLS(), "CY_INST");
      DFSF.SkipInsts.insert(LI);
      DFSF.setShadow(CS.getInstruction(), LI);
      DFSF.NonZeroChecks.push_back(LI);
    }
  }

  // Do all instrumentation for IA_Args down here to defer tampering with the
  // CFG in a way that SplitEdge may be able to detect.
  if (DFSF.DFS.getInstrumentedABI() == DataFlowSanitizer::IA_Args) {
    FunctionType *NewFT = DFSF.DFS.getArgsFunctionType(FT);
    Value *Func =
        IRB.CreateBitCast(CS.getCalledValue(), PointerType::getUnqual(NewFT), "CY_INST");
    std::vector<Value *> Args;

    CallSite::arg_iterator i = CS.arg_begin(), e = CS.arg_end();
    for (unsigned n = FT->getNumParams(); n != 0; ++i, --n)
      Args.push_back(*i);

    i = CS.arg_begin();
    for (unsigned n = FT->getNumParams(); n != 0; ++i, --n)
      Args.push_back(DFSF.getShadow(*i));

    if (FT->isVarArg()) {
      unsigned VarArgSize = CS.arg_size() - FT->getNumParams();
      ArrayType *VarArgArrayTy = ArrayType::get(DFSF.DFS.ShadowTy, VarArgSize);
      AllocaInst *VarArgShadow =
        new AllocaInst(VarArgArrayTy, getDataLayout().getAllocaAddrSpace(),
                       //"", &DFSF.F->getEntryBlock().front());
                       "CY_INST", &DFSF.F->getEntryBlock().front());
      Args.push_back(IRB.CreateConstGEP2_32(VarArgArrayTy, VarArgShadow, 0, 0, "CY_INST"));
      for (unsigned n = 0; i != e; ++i, ++n) {
        IRB.CreateStore(
            DFSF.getShadow(*i),
            IRB.CreateConstGEP2_32(VarArgArrayTy, VarArgShadow, 0, n, "CY_INST"));
        Args.push_back(*i);
      }
    }

    CallSite NewCS;
    if (InvokeInst *II = dyn_cast<InvokeInst>(CS.getInstruction())) {
      NewCS = IRB.CreateInvoke(Func, II->getNormalDest(), II->getUnwindDest(),
                               Args, "CY_INST");
    } else {
      NewCS = IRB.CreateCall(Func, Args, "CY_INST");
    }
    NewCS.setCallingConv(CS.getCallingConv());
    NewCS.setAttributes(CS.getAttributes().removeAttributes(
        *DFSF.DFS.Ctx, AttributeList::ReturnIndex,
        AttributeFuncs::typeIncompatible(NewCS.getInstruction()->getType())));

    if (Next) {
      ExtractValueInst *ExVal =
          //ExtractValueInst::Create(NewCS.getInstruction(), 0, "", Next);
          ExtractValueInst::Create(NewCS.getInstruction(), 0, "CY_INST", Next);
      DFSF.SkipInsts.insert(ExVal);
      ExtractValueInst *ExShadow =
          //ExtractValueInst::Create(NewCS.getInstruction(), 1, "", Next);
          ExtractValueInst::Create(NewCS.getInstruction(), 1, "CY_INST", Next);
      DFSF.SkipInsts.insert(ExShadow);
      DFSF.setShadow(ExVal, ExShadow);
      DFSF.NonZeroChecks.push_back(ExShadow);

      CS.getInstruction()->replaceAllUsesWith(ExVal);
    }

    CS.getInstruction()->eraseFromParent();
  }
}

void DFSanVisitor::visitPHINode(PHINode &PN) {
  PHINode *ShadowPN =
      //PHINode::Create(DFSF.DFS.ShadowTy, PN.getNumIncomingValues(), "", &PN);
      PHINode::Create(DFSF.DFS.ShadowTy, PN.getNumIncomingValues(), "CY_INST", &PN);

  // Give the shadow phi node valid predecessors to fool SplitEdge into working.
  Value *UndefShadow = UndefValue::get(DFSF.DFS.ShadowTy);
  for (PHINode::block_iterator i = PN.block_begin(), e = PN.block_end(); i != e;
       ++i) {
    ShadowPN->addIncoming(UndefShadow, *i);
  }

  DFSF.PHIFixups.push_back(std::make_pair(&PN, ShadowPN));
  DFSF.setShadow(&PN, ShadowPN);
}
