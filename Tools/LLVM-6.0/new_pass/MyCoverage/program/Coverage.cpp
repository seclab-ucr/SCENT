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
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include "llvm/ADT/StringExtras.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/IR/CallSite.h"


#define CY_Version1 0
#define IS_FREEBSD 1

using namespace llvm;
using namespace std;

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

  	static Function* pkt_output_prototype(LLVMContext& ctx, Module *mod) {
    	Function *func = mod->getFunction("Packet_Output");
    	if(!func)
            errs() << "Packet_Output is not defined\n";
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
        if (I == NULL)
            return "--- ";
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

    struct myCoverage : public ModulePass {
        static char ID;
		LLVMContext *context;
        myCoverage() : ModulePass(ID) {}
		
		GlobalVariable *FmtStr;
        GlobalVariable *BasicBlockProfilingStr = NULL;
        GlobalVariable *BasicBlockCountFmtStr = NULL;
		GlobalVariable *EdgeProfilingStr = NULL;
    	GlobalVariable *EdgeCountFmtStr = NULL;
		Function *printf_func = NULL;
        Function *pkt_output_func = NULL;
        const char *basic_block_count_fmt_str = " b%d: %d\n";
		const char *format = " CMP %d with constants %d\n";

		std::vector<GlobalVariable*> bbCounters;
		std::vector<std::pair<unsigned int, unsigned int>> edges;
		std::vector<unsigned int> bbID;
		std::vector<GlobalVariable*> edgeCounters;
		std::vector<std::string> bbLines;
        //std::set<std::string> Target_File;
        //std::set<std::string> Target_Function;
        SmallPtrSet<Function*, 32> VisitedFuncs;
        std::set<unsigned int>Target_BB;

        unsigned int block_num = 0;
        unsigned int new_block_num = 0;
        std::vector<unsigned int>M0_block;
        std::vector<unsigned int>M1_block;

        void traverse(CallGraphNode *node, Module &Mod) {
            VisitedFuncs.insert(node->getFunction());
            for (auto &BB : *(node->getFunction()))
                runOnBasicBlock(BB, &Mod);
            for (CallGraphNode::iterator I = node->begin(), E = node->end(); I != E; ++I) {
                /*
                if (I->first){
                    CallSite CS(I->first);
                    Value *V = CS.getCalledValue();
                    errs() << "First: " << V->getName() << "\n";
                    errs() << "First2: " << *V << "\n";
                    if (CS.isIndirectCall()){
                        LoadInst *LI = cast<LoadInst>(V);
                        errs() << "Load: " << *LI << "\n";
                    }
                }
                */
                if (Function *F = I->second->getFunction()){
                    if (VisitedFuncs.find(F) != VisitedFuncs.end())
                        continue;
                    errs() << "Second: " << F->getName() << "\n";
                    traverse(I->second, Mod);
                }
                //TODO: add current result into Target_Function
            }
        }
		

		bool doInitialization(Module &M) override {
			context = &M.getContext();
			//FmtStr = global_string(*context, &M, format, "Formate");
			printf_func = printf_prototype(*context, &M);
            pkt_output_func = pkt_output_prototype(*context, &M);

            /*
            string line;
            ifstream inFile("../Source_Code/File_included.txt");
            //ifstream inFile("File_included.txt");
            while (getline(inFile, line)){
                Target_File.insert(line);
            }
            inFile.close();
           
            string line2;
            ifstream inFile2("../called_function.txt");
            //ifstream inFile("File_included.txt");
            while (getline(inFile2, line2)){
                Target_Function.insert(line2);
            }
            inFile2.close();
            */

            block_num = 0;
            for (auto &F : M)
                for (auto &BB : F){
                    if (F.getName().startswith("Model0"))
                        M0_block.push_back(block_num);
                    if (F.getName().startswith("Model1"))
                        M1_block.push_back(block_num);
                    /*
                        BB.setName("M0b" + utostr(M0_block_num++)); //used it temporarily, which is consistent with previous analysis regarding coverage rate.
                    if (F.getName().startswith("Model1"))
                        BB.setName("M1b" + utostr(M1_block_num++));
                    */
                    BB.setName("b" + utostr(block_num++));
                    //BB.setName(F.getName()+"-b" + utostr(block_num++)); //It requires more modifications
                }

            const char *basic_block_profiling_str = "\nBASIC BLOCK PROFILING: \n";
            BasicBlockProfilingStr = global_string(*context, &M, basic_block_profiling_str, "BasicBlockProfilingStr");
            //BasicBlockCountFmtStr = global_string(*context, &M, basic_block_count_fmt_str, "BasicBlockCountFmtStr");
			const char *edge_profiling_str = "\nEDGE PROFILING: \n";
      		const char *edge_count_fmt_str = "b%d -> b%d: %d\n";
			EdgeProfilingStr = global_string(*context, &M, edge_profiling_str, "EdgeProfilingStr");
      		EdgeCountFmtStr = global_string(*context, &M, edge_count_fmt_str, "EdgeCountFmtStr");
            //errs() << "-------End of Initialization --------\n";
            //
            errs() << "M0_block size: " << M0_block.size() << "\n";
            errs() << "M1_block size: " << M1_block.size() << "\n";

            unsigned int M0_max = 0;
            for (int i = 0; i < M0_block.size(); i++){
                M0_max = max(M0_max, M0_block[i]);
                errs() << M1_block[i]-M0_block[i] << ",";
            }
            errs() << "\n";
            errs() << "M0_max: " << M0_max << "\n";
            return true;
		}


        bool runOnModule(Module &Mod) override {
			//Module *M = &Mod;
			context = &Mod.getContext();
            
			std::vector<Constant*> indices;
			Constant *zero = Constant::getNullValue(IntegerType::getInt32Ty(*context));
			indices.push_back(zero);
			indices.push_back(zero);
			
			Constant *var_ref;
                            
            Value *firstOperand;
            Value *secondOperand;

            bool compared = false;

#if IS_FREEBSD
            Function* ENTRY = Mod.getFunction("Model0_tcp_input");
#else
            Function* ENTRY = Mod.getFunction("Model0_tcp_v4_rcv");
#endif
            //Function* ENTRY = Mod.getFunction("Model0_tcp_rcv_established");
            errs() << ENTRY->getName() << "\n";
            CallGraph &CG = getAnalysis<CallGraphWrapperPass>().getCallGraph();
            CallGraphNode *node = CG[ENTRY];
            traverse(node, Mod);
     
#if IS_FREEBSD
            ENTRY = Mod.getFunction("Model1_tcp_input");
#else
            ENTRY = Mod.getFunction("Model1_tcp_v4_rcv");
#endif
            //ENTRY = Mod.getFunction("Model1_tcp_rcv_established");
            errs() << ENTRY->getName() << "\n";
            node = CG[ENTRY];
            traverse(node, Mod);
            
           
            /*
            for (auto &F: Mod){
                for (auto &BB: F){
                    runOnBasicBlock(BB, &Mod);
                }
            }
            */

            //Function* F2 = Mod.getFunction("r_ck");
            Function* F2 = Mod.getFunction("Instrument_Summary");
			for (auto &BB : *F2) {
				if (isa<ReturnInst>(BB.getTerminator())) {
				//if (F.getName().equals("dfs$r_ck") && isa<ReturnInst>(BB.getTerminator())) {
				//if (F.getName().equals("report_time") && isa<ReturnInst>(BB.getTerminator())) {
				//if (F.getName().equals("main") && isa<ReturnInst>(BB.getTerminator())) {
					addFinalPrintf(BB);
				}
			}
            return true;
        }
		
        void getAnalysisUsage(AnalysisUsage &AU) const override {
        	AU.setPreservesAll();
        	AU.addRequired<CallGraphWrapperPass>();
    	}

        bool runOnBasicBlock(BasicBlock &BB, Module *M){
            if (BB.getName().startswith("newBB")) {
                //errs() << BB.getName() << " is a new block. skip.\n";
                return false;
            }
            unsigned int block_ID, succ_ID;
            BB.getName().substr(1).getAsInteger(10, block_ID);

            errs() << "BB name: " << BB.getName() << "\n";
            errs() << "blockID: " << block_ID << "\n";

            IRBuilder<> builder(&BB, BB.getFirstInsertionPt());
            Value *loadAddr, *addAddr;
			TerminatorInst *TI = BB.getTerminator();

            /* BASIC BLOCK PROFILING */
            /* create counter for current basic block */
			GlobalVariable *bbCounter = new GlobalVariable(*M, Type::getInt32Ty(*context), false, GlobalValue::InternalLinkage, ConstantInt::get(Type::getInt32Ty(*context), 0), "bbCounter" + utostr(block_ID));
			bbCounters.push_back(bbCounter);
            bbID.push_back(block_ID);
           
            std::string bbLine;
#if CY_Version1
            Instruction *II;
            II = &(BB.front());
            if (II->isTerminator())
                bbLine = getLineNumber(II);
            while (!II->isTerminator()){
                bbLine = getLineNumber(II);
                //errs() << *II << " : " << bbLine << "\n";
                if (bbLine.find("File: - ") == -1)
                    break;
                else{
                    II = II->getNextNode();
                }
            }
            if (bbLine.find("File: - ") != -1){
                errs() << BB.getName() << "\n";
            }

            
            //errs() << "BBLine: " << bbLine << "\n";
            int p1 = bbLine.find("Line");
            //errs() << "P1: " << p1 << "\n";
            std::string tmpLine = bbLine.substr(6,p1-1-6);
            //errs() << "Current file: " << tmpLine << "\n";
            if (Target_File.count(tmpLine) != 0){
                //errs() << "Target_file: " << tmpLine << "\n";
                //errs() << "block_ID: " << block_ID << "\n";
                Target_BB.insert(block_ID);
            }
#else //Use callgraph to traverse 
            bbLine = getLineNumber(&(BB.front()));
            Function *F2 = BB.getParent();
            errs() << "block_ID0\n";
            if (VisitedFuncs.find(F2) != VisitedFuncs.end()){
            //if (Target_Function.count(F2->getName()) != 0){
                Target_BB.insert(block_ID);
                errs() << "block_ID: " << block_ID << "\n";
            }
#endif
            bbLines.push_back(bbLine);
			// insert basic block profiling instructions 
			loadAddr = builder.CreateLoad(bbCounter);
			addAddr = builder.CreateAdd(builder.getInt32(1), loadAddr);
			builder.CreateStore(addAddr, bbCounter);

			/* EDGE PROFILING */
            //errs() << "Start of EDGE Profiling\n";
			if (TI->getNumSuccessors() == 1) {
                /*
				BasicBlock *SBB = TI->getSuccessor(0);
				SBB->getName().substr(1).getAsInteger(10, succ_ID);
				// create counter for edge 
				GlobalVariable *edgeCounter = new GlobalVariable(*M, Type::getInt32Ty(*context), false, GlobalValue::InternalLinkage, ConstantInt::get(Type::getInt32Ty(*context), 0), "edgeCounter" + utostr(block_ID) + "_" + utostr(succ_ID));
				edgeCounters.push_back(edgeCounter);
				edges.push_back(std::pair<unsigned int, unsigned int>(block_ID, succ_ID));
				// insert edge profiling instructions 
				IRBuilder<> builder2(&BB, BB.getFirstInsertionPt());
				loadAddr = builder2.CreateLoad(edgeCounter);
				addAddr = builder2.CreateAdd(builder2.getInt32(1), loadAddr);
				builder2.CreateStore(addAddr, edgeCounter);
                */
            }
            else {
                for (unsigned s = 0; s < TI->getNumSuccessors(); ++s) {
                    BasicBlock *SBB = TI->getSuccessor(s);
                    SBB->getName().substr(1).getAsInteger(10, succ_ID);

                    //errs() << "succ_ID: " << succ_ID << "\n";

                    auto I = pred_begin(SBB), E = pred_end(SBB);
                    if (I != E) {
                        I++;
                        if (I != E) {
                            // this is a critical edge, need to split 
                            BasicBlock *newBB = BasicBlock::Create(*context, "newBB"+utostr(new_block_num++), BB.getParent(), SBB); TI->setSuccessor(s, newBB);
                            //BranchInst::Create(newBB, SBB);
                            BranchInst::Create(SBB, newBB);
							for (BasicBlock::phi_iterator PS = SBB->phis().begin(); PS != SBB->phis().end(); PS++){
								 //errs() << "Phi Node: " << *PS << "\n";
								 BasicBlock *IncomingBB;
								 int op_num = PS->getNumOperands();
								 for (int i = 0; i < op_num; i++){
									 IncomingBB = PS->getIncomingBlock (i);
									 //errs() << "IncomingBB: " << *IncomingBB << "\n";
									 if (IncomingBB == &BB){
										 PS->setIncomingBlock(i, newBB);
									 }
								 }
							 }
                        }
                    }



					/* create counter for edge */
				  	GlobalVariable *edgeCounter = new GlobalVariable(*M, Type::getInt32Ty(*context), false, GlobalValue::InternalLinkage, ConstantInt::get(Type::getInt32Ty(*context), 0), "edgeCounter" + utostr(block_ID) + "_" + utostr(succ_ID));
				  	edgeCounters.push_back(edgeCounter);
				  	edges.push_back(std::pair<unsigned int, unsigned int>(block_ID, succ_ID));
				  	/* insert edge profiling instructions */

				  	IRBuilder<> builder2(TI->getSuccessor(s), TI->getSuccessor(s)->getFirstInsertionPt());
				  	loadAddr = builder2.CreateLoad(edgeCounter);
				  	addAddr = builder2.CreateAdd(builder2.getInt32(1), loadAddr);
				  	builder2.CreateStore(addAddr, edgeCounter);
                }
            }
			return true;
		}

		void addFinalPrintf(BasicBlock& BB) {
            Module *M = BB.getParent()->getParent();
            context = &M->getContext();
			IRBuilder<> builder(BB.getTerminator());
			CallInst *call;
			Constant *var_ref;

			std::vector<Constant*> indices;
			Constant *zero = Constant::getNullValue(IntegerType::getInt32Ty(*context));
			indices.push_back(zero);
			indices.push_back(zero);

            // print basic block profiling result
            var_ref = ConstantExpr::getGetElementPtr(NULL, BasicBlockProfilingStr, indices);
            call = builder.CreateCall(printf_func, var_ref);
            call->setTailCall(false);

            std::string tmp_str;
            std::string tmp_str0 (basic_block_count_fmt_str);
            std::string tmp_str1 ("BasicBlockProfilingStr");
            //var_ref = ConstantExpr::getGetElementPtr(NULL, BasicBlockCountFmtStr, indices);
            GlobalVariable *newBasicBlockCountFmtStr;
            for (unsigned int i = 0; i < bbCounters.size(); i++) {
                if (Target_BB.count(bbID[i]) == 0)
                    continue;
                Value *Count = builder.CreateLoad(bbCounters[i]);
                //if (bbLines[i].find("Model0") == -1)
                //    continue;
                tmp_str = bbLines[i] + tmp_str0;
                //errs() << tmp_str << "\n";
                newBasicBlockCountFmtStr = global_string(*context, M, tmp_str.c_str(), (tmp_str1+utostr(i)).c_str());
                var_ref = ConstantExpr::getGetElementPtr(NULL, newBasicBlockCountFmtStr, indices);
                //errs() << tmp_str1+utostr(i) << "\n";
                //errs() << "End\n";
                call = builder.CreateCall(printf_func, {var_ref, builder.getInt32(bbID[i]), Count});
                errs() << "BasicProfile\n";
                call->setTailCall(false);
            }

            /* print edge profiling result */
			var_ref = ConstantExpr::getGetElementPtr(NULL, EdgeProfilingStr, indices);
		  	call = builder.CreateCall(printf_func, var_ref);
		  	call->setTailCall(false);

		  	var_ref = ConstantExpr::getGetElementPtr(NULL, EdgeCountFmtStr, indices);
		  	for (unsigned int i = 0; i < edgeCounters.size(); i++) {
                if (Target_BB.count(edges[i].first) == 0 || Target_BB.count(edges[i].second) == 0)
                    continue;
				Value *Count = builder.CreateLoad(edgeCounters[i]);
				call = builder.CreateCall(printf_func, {var_ref, builder.getInt32(edges[i].first),
						builder.getInt32(edges[i].second), Count});
				call->setTailCall(false);
		  	};

            call = builder.CreateCall(pkt_output_func, {});
            call->setTailCall(false);

        }	
			
    };
}

char myCoverage::ID = 0;
static RegisterPass<myCoverage> X("myCoverage", "Instrumentation Pass for Model Checker", false, false);
