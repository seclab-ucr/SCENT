#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/TypeFinder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include<set>
#include <fstream>

#define IS_LINUX 0
using namespace llvm;
using namespace std;

namespace {
    struct myFunctionPointer : public ModulePass {
        static char ID;
        bool called = false;
        set<string>Location;
        set<string>Called_Function;

        SmallPtrSet<Function*, 32> VisitedFuncs;
        myFunctionPointer() : ModulePass(ID) {}


        void traverse(CallGraphNode *node){
            VisitedFuncs.insert(node->getFunction());

            for (CallGraphNode::iterator I = node->begin(), E = node->end(); I != E; I++){
                if (I->first){
                    CallSite CS(I->first);
                    if (CS.isIndirectCall()){
                        Instruction *Inst = CS.getInstruction();
                        errs () << "function pointer: " << *Inst << "\n";
                        const DILocation *Loc = Inst->getDebugLoc();
                        if (Loc){
                            unsigned Line0 = Loc->getLine();
                            StringRef File = Loc->getFilename();
                            string temp = to_string(Line0)+":"+(string)File;
                            Location.insert(temp);
                        }
                    }
                    else{
                        if (Function *F = I->second->getFunction()){
                            if (VisitedFuncs.find(F) != VisitedFuncs.end())
                                continue;
                            errs() << F->getName() << "\n";
                            traverse(I->second);
                        }
                    }
                }
            }
        }
        bool runOnModule(Module &M) override {
		   string function_name;
           Value * Fun;
           Instruction *II;
           for (auto &F : M){
               //if (F.getName().find("tcp_v4_rcv") == string::npos)
#if IS_LINUX
               if (F.getName() != "Model0_tcp_v4_rcv")
#else //FreeBSD
               if (F.getName() != "Model0_tcp_input")//"Model0_tcp_v4_rcv")
#endif
                   continue;

               errs() << F.getName() << "\n";
               CallGraph &CG = getAnalysis<CallGraphWrapperPass>().getCallGraph();
               CallGraphNode *node = CG[&F];

               traverse(node);
           }

           for (set<string>::iterator Lit = Location.begin(); Lit != Location.end(); Lit++)
               errs() << *Lit << "\n";
           return false;
        }
        
        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesAll();
            AU.addRequired<CallGraphWrapperPass>();
        }
    };
}

char myFunctionPointer::ID = 0;
static RegisterPass<myFunctionPointer> X("myfunctionpointer", "Hello World Pass", false, false);
