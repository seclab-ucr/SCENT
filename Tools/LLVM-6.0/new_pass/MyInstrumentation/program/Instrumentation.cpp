#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/CFG.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/LoopInfo.h"
#include <llvm/Transforms/Utils/Local.h>
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/IntrinsicInst.h"
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallPtrSet.h"


#include "llvm/ADT/StringExtras.h"

#define OFFSET_BASE 200

using namespace llvm;

namespace {

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

  	static Function* pkt_track_prototype(LLVMContext& ctx, Module *mod) {
    	std::vector<Type*> printf_arg_types;
    	printf_arg_types.push_back(Type::getInt8PtrTy(ctx));
 
    	FunctionType *printf_type = FunctionType::get(Type::getInt32Ty(ctx), printf_arg_types, true);
    	Function *func = mod->getFunction("Packet_Track_Insert");
    	if(!func)
            errs() << "Packet_Track_Insert is not defined\n";
    	func->setCallingConv(CallingConv::C);
    	return func;
  	}

  	static GlobalVariable* global_string(LLVMContext& ctx, Module *mod, const char *str, const char *name) {
    	return new GlobalVariable(
            *mod, 
            llvm::ArrayType::get(llvm::IntegerType::get(ctx, 8), strlen(str)+1), 
            true, 
            llvm::GlobalValue::PrivateLinkage, 
            ConstantDataArray::getString(ctx, str), 
            name);
  	}

	
	//Constant* metadata::getLineNumber(Instruction* I){
	std::string getLineNumber(Instruction* I){
    	if (MDNode *N = I->getMetadata("dbg")) { // this if is never executed
        	DILocation* Loc = I->getDebugLoc();
        	unsigned Line = Loc->getLine();
			//std::string str("File: ");
			//return Line;
			//str = str + Loc->getFilename().data() + " Line: " + std::to_string(Line);
            std::string str = "Line: " + std::to_string(Line);
			return str;
        	//return ConstantInt::get(Type::getInt32Ty(I->getContext()), Line);
    	}else {
      		return "Line: - "; 
		}
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

    std::string getBBOffsetStr(Instruction* I, int &BB_OffsetInt){
        BasicBlock *BB = I->getParent();
        int count = 0;
        for (BasicBlock::iterator II=BB->begin(); II != BB->end(); II++){
            if (IntrinsicInst *ii = dyn_cast<IntrinsicInst>(&*II)){
                switch(ii->getIntrinsicID()){
                    case Intrinsic::vastart:
                    case Intrinsic::vaend:{
                        break;
                    }
                    case Intrinsic::vacopy: {
                        assert(0 && "todo: handle intrinsic::vacopy");
                        break;
                    }
                    case Intrinsic::sadd_with_overflow:
                    case Intrinsic::ssub_with_overflow:
                    case Intrinsic::smul_with_overflow:
                    case Intrinsic::uadd_with_overflow:
                    case Intrinsic::usub_with_overflow:
                    case Intrinsic::umul_with_overflow: {
                        assert(0 && "todo: handle intrinsic::****_with_overflow");
                        break;
                    } 
                    case Intrinsic::dbg_value:
                    case Intrinsic::dbg_declare:{
                        count--;
                        break;
                    }
                    case Intrinsic::trap: {
                        assert(0 && "todo: handle intrinsic::trap");
                        break;
                    }
                    case Intrinsic::objectsize: {
                        assert(0 && "todo: handle intrinsic::objectsize");
                        break;
                    }
                    default:
                        break;
                }
            }
            else if ((*II).getName().startswith("CY_INST"))
                count--;
            else if (CallInst *CI = dyn_cast<CallInst>(II)){
                if (CI->isInlineAsm())
                    count--;
            }

            count++;
            if (&*II == I){
                break;
            }
        }
        //return BB->getName().str() + ":" + std::to_string(count+3);//+1 since we will add CALL print instruction, +2 since we add 2 castinst
        BB_OffsetInt = std::stoi(BB->getName().substr(1))*OFFSET_BASE + count;

        return BB->getName().str() + ":" + std::to_string(count);//We update offset during replacement
    }

    struct myInstrumentation : public FunctionPass {
        static char ID;
		LLVMContext *context;
        myInstrumentation() : FunctionPass(ID) {}
		
		GlobalVariable *FmtStr;
		GlobalVariable *NOP;
        GlobalVariable *BasicBlockProfilingStr;
		Function *printf_func = NULL;
        Function *pkt_track_func = NULL;
		Constant *nop;

        unsigned Not_CMP_Count = 0, CMP_Count = 0;
		//const char *format = " CMP %d with %d\n";
		const char *format_ss = " CMP %lld with %lld\n";
		const char *format_uu = " CMP %llu with %llu\n";

		bool doInitialization(Module &M) override {
			context = &M.getContext();
			//FmtStr = global_string(*context, &M, format, "Formate");
			printf_func = printf_prototype(*context, &M);
            pkt_track_func = pkt_track_prototype(*context, &M);

            const char *basic_block_profiling_str = "\nBASIC BLOCK PROFILING: \n";
            BasicBlockProfilingStr = global_string(*context, &M, basic_block_profiling_str, "BasicBlockProfilingStr");
            //errs() << "-------End of Initialization --------\n";
            NOP = global_string(*context, &M, "", "NOP");
			
            std::vector<Constant*> indices;
			Constant *zero = Constant::getNullValue(IntegerType::getInt32Ty(*context));
			indices.push_back(zero);
			indices.push_back(zero);
            
            //StructFieldMap(&M, "Model0_Replace_DEBUG", indices);
            //StructFieldMap(&M, "Model1_Replace_DEBUG", indices);
            //StructFieldMap(&M, "Packet_Replace_DEBUG", indices);
            return true;
        }
	    


        std::string print_format(unsigned Width, bool isSigned){
            switch(Width) {
                case 64: return isSigned? "\%lld" : "\%llu";
                case 32: return isSigned? "\%d" : "\%u";
                case 16: return isSigned? "\%hd" : "\%hu";
                case 8: return isSigned? "\%hd" : "\%hu";
                default: return "ERROR";
            }
        }

        void CI_Instrumentation(Instruction &I, std::vector<Constant*> indices, Module *M){
            std::string tmpFileName = getFile(&I);
            std::string Prefix;
            if (tmpFileName.find("Model") == -1) //We should not filter Model1 here, since it will make model1's basic offset not consistent with model0
              return;
            if (tmpFileName.find("Model0") != -1)
                Prefix = "Model0";
            else
                Prefix = "Model1";

            CmpInst *CI = dyn_cast<CmpInst>(&I);
			Constant *var_ref;
                            
            Value *firstOperand;
            Value *secondOperand;

            Value *tmp_first;
            Value *tmp_second;

            //if (CI->isEquality())
            //    return;
            
            if (CI->getNumOperands() >= 2){
                //errs() << *CI << "\n";
                firstOperand = CI->getOperand(0);
                secondOperand;
                //if (isa<ConstantInt>(firstOperand))
                //    CI->swapOperands();
                firstOperand = CI->getOperand(0);
                secondOperand = CI->getOperand(1);
                //if (!isa<ConstantInt>(secondOperand))
                //    return;

                IRBuilder<> builder(CI);

                //unsigned line = getLineNumber(&I);




               
                CallInst *call;
                nop = ConstantExpr::getGetElementPtr(NULL, NOP, indices);

                if (!firstOperand->getType()->isIntOrIntVectorTy()|| !secondOperand->getType()->isIntOrIntVectorTy()){
                    int temp;
                    
                    std::string BB_INFO = Prefix + "," + getBBOffsetStr(&I, temp); //Prefix here is used to filter Model1 later, since we only transform program based on Model0
                    //std::string BB_INFO = getFile(&I) + "," + getBBOffsetStr(&I, temp);
                    errs() << "Not Int:" << BB_INFO << "," << getLineNumber(&I) << "\n";
                    //call = builder.CreateCall(printf_func, {var_ref, firstOperand, secondOperand}, "CY_INST");
                    return;
                }
                else{
                    std::string format = "CMP ";
		            //const char *format_ss = " CMP %lld with %lld\n";
                    unsigned firstBitWidth = (cast<IntegerType>(firstOperand->getType()))->getBitWidth();
                    unsigned secondBitWidth = (cast<IntegerType>(secondOperand->getType()))->getBitWidth();
                    format += print_format(firstBitWidth, CI->isSigned()) + " with " + print_format(secondBitWidth, CI->isSigned()) + "\n";
                    
                    std::string tmp_str(format);
                    int BB_offset;
                    //tmp_str = "Line: " + std::to_string(line) + tmp_str;
                    std::string BB_INFO = Prefix + "," + getBBOffsetStr(&I, BB_offset);
                    //std::string BB_INFO = getFile(&I) + "," + getBBOffsetStr(&I, BB_offset);
                    tmp_str = BB_INFO + "|" + CmpInst::getPredicateName(CI->getPredicate()).str() + "|" + tmp_str;
                    errs() << BB_INFO << "," << getLineNumber(&I) << "\n";
                    std::string SourceCodeINFO = getFile(&I);
                    //if (SourceCodeINFO.find("pan") != -1 || SourceCodeINFO.find("-") != -1)
                    if (SourceCodeINFO.find("tcp_input") == -1) //we don't care about Initialization, especially we don't care what packets would reach to such branch condition
                        return;
                    CMP_Count++;
                    FmtStr = global_string(*context, M, tmp_str.c_str(), "Formate");

                    var_ref = ConstantExpr::getGetElementPtr(NULL, FmtStr, indices);


                    tmp_first = builder.CreateIntCast(firstOperand, Type::getInt64Ty(M->getContext()), true, "CY_INST");
                    tmp_second = builder.CreateIntCast(secondOperand, Type::getInt64Ty(M->getContext()), true, "CY_INST");
                    call = builder.CreateCall(printf_func, {var_ref, tmp_first, tmp_second}, "CY_INST");
                    call->setTailCall(false);

                    CallInst *call2;
                    errs() << BB_offset << "\n";
                    call2 = builder.CreateCall(pkt_track_func, {builder.getInt32(BB_offset)}, "CY_INST");
                    call->setTailCall(false);
                    errs() << *call2 << "\n";
                }
            }
        }
   
        void StructFieldMap(Module *M, std::string F_name, std::vector<Constant*> indices){
            Function *F = M->getFunction(F_name);
            int pos, count;
            GlobalVariable *G_tmp;
            Constant *var_ref;
            CallInst *call;
            for (auto &BB: *F){
                for (auto &I: BB){
                    if (isa<CallInst>(I)){
                        if (I.getName().find("CY_INST2")!=-1){
                            printf("Repeat adding\n");
                            continue;
                        }
                        //errs() << "Original: " << I << "\n";
                        std::string temp;
                        raw_string_ostream OS(temp);
                        OS << I;
                        OS.flush();
                        //std::string temp = stream.str();
                        pos = temp.rfind("getelementptr");
                        if (pos == temp.find("getelementptr")) //Only handle struct fields or array
                            continue;
                        pos = temp.substr(0, pos).rfind(",");
                        //errs() << "Tmp target: " << temp << "\n";
                        temp = temp.substr(pos+2, temp.length()-pos-2);
                        pos = temp.rfind(")");
                        temp = temp.substr(0, pos);
                        temp = temp+"\n";

                        //std::replace(temp.begin(), temp.end(), '%', "\\%");
                        std::string temp2 = temp;
                        int index = 0;
                        while (true){
                            pos = temp2.find("%s");
                            if (pos == -1)
                                break;
                            temp.insert(index+pos, "%");
                            temp2 = temp2.substr(pos+2, temp2.length()-pos-2);
                            index += (pos+2+1);
                        }
                        //errs() << "target: " << temp.c_str();

                        IRBuilder<> builder(&I);

                        //G_tmp = global_string(*context, M, temp.c_str(), "CY_StructFieldMap");
                        G_tmp = global_string(*context, M, temp.c_str(), "CY_INST2");
                        var_ref = ConstantExpr::getGetElementPtr(NULL, G_tmp, indices);
                        call = builder.CreateCall(printf_func, var_ref, "CY_INST2");
                        call->setTailCall(false);
                        errs() << "DEBUG: " << *call << "\n";
                        //Rest case is global variable. We will replace their initializor. 
                    }
                }
            }
        }

        bool runOnFunction(Function &F) override {
			Module *M = F.getParent();
			context = &M->getContext();
            

			std::vector<Constant*> indices;
			Constant *zero = Constant::getNullValue(IntegerType::getInt32Ty(*context));
			indices.push_back(zero);
			indices.push_back(zero);
			

            SmallPtrSet<Instruction*, 8> Visited;
            SmallVector<Instruction*, 8> WorkList;

            bool compared = false;
            for (auto &B: F){
                TerminatorInst *TI = B.getTerminator();
                if (BranchInst *Br = dyn_cast<BranchInst>(TI)){
                    if (Br->isUnconditional())
                        continue;
                    Value *V = Br->getCondition();
                    /*
                    if (Instruction *INST = dyn_cast<Instruction>(V)){
                        if (!isa<ICmpInst>(INST))
                            errs() << INST->getOpcodeName() << " : " << *V << "\n";
                        //errs() << "Branch Condition: " << INST->getOpcodeName() << "\n";
                    }*/

                    if (Instruction *VI = dyn_cast<Instruction>(V)){
                        //errs() << "Instruction: " << *VI << "\n";
                        //errs() << "BB information: " << getBBOffsetStr(VI) << "\n";
                        if (!isa<CmpInst>(VI)){
                            std::string FileName = getFile(VI);
                            if (FileName.find("Model") == -1) //We should not filter Model1 here, since it will make model1's basic offset not consistent with model0
                                continue;
                            //errs() << *VI << "\n";
                            //errs() << getFile(VI) + "," + getBBOffsetStr(VI) << "\n";
                            Not_CMP_Count++;
                        }
                        Visited.clear();
                        WorkList.clear();
                        Visited.insert(VI);
                        WorkList.push_back(VI);
                        while(!WorkList.empty()){
                            Instruction *cur = WorkList.pop_back_val();
                            /* If we use O2 to compile the source code, branch conditon will be only ICMP, And/Or Binary Operator, call inst (only 2 without icmp), PHI (related to basic block, instead of ICMP. So here we only care about ICMP and Binary Operator */
                            if (isa<CmpInst>(cur)){
                                CI_Instrumentation(*cur, indices, M);
                                continue;
                            }
                            /*
                            if (isa<CallInst>(cur)){
                                StringRef name = cur->getCalledFunction().getName();
                                Function *F = M->getFunction(name);
                                //we only care about ICMP before BranchInst, since the other ICMPs are counted alreayd
                                if (!F->doesNotReturn()){
                                    for (BasicBlock &BB : *F) {
                                        const TerminatorInst *T = BB.getTerminator();
                                        if (const ReturnInst *R = dyn_cast<ReturnInst>(T)){
                                            Value *v = R->getReturnValue();
                                            if (Instruction *next = dyn_cast<Instruction>(v)){
                                                if (Visited.insert(next).second)
                                                    WorkList.push_back(next);
                                            }
                                        }
                                    }
                                }
                                continue;
                            }
                            */


                            std::string temp = cur->getOpcodeName();
                            if (temp == "and" || temp == "or")
                                for (Use &U : cur->operands()){
                                    Value *v = U.get();
                                    if (Instruction *next = dyn_cast<Instruction>(v)){
                                        //errs() << "Others: " << *next << "\n";
                                        if (Visited.insert(next).second){
                                            WorkList.push_back(next);
                                        }
                                    }
                                }
                            }

                            /*
                            for (Use &U : cur->operands()){
                                Value *v = U.get();
                                if (Instruction *next = dyn_cast<Instruction>(v)){
                                    //errs() << "Others: " << *next << "\n";
                                    if (BinaryOperator *BO = dyn_cast<BinaryOperator>(next))
                                        if (BO->isLogicalOp() && Visited.insert(next).second){
                                            WorkList.push_back(next);
                                        }
                                }
                            }*/
                    }
                }
                /*
                for (auto &I: B){
                    if (isa<CmpInst>(I))
                        CI_Instrumentation(I, indices, M);
                }
                */
            }
            //errs() << "Not ICMP Count: " << Not_CMP_Count << "\n";
            //errs() << "ICMP Count: " << CMP_Count << "\n";
            return true;
        }
    };
}

char myInstrumentation::ID = 0;
static RegisterPass<myInstrumentation> X("myInstrumentation", "Instrumentation Pass for Model Checker", false, false);
