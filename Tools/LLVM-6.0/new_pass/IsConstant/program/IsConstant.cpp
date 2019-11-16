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
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallPtrSet.h"


#include "llvm/ADT/StringExtras.h"

#define OFFSET_BASE 200

using namespace llvm;

namespace {

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

    void findBBOffset(BasicBlock *BB, std::string BB_Offset){
        int p0 = BB_Offset.find(",");
        int p1 = BB_Offset.rfind(":");
        int p2 = BB_Offset.find("|");
        int p3 = BB_Offset.find("#");
        int p5 = BB_Offset.rfind("#");
        int p4 = BB_Offset.substr(p3+1, p5-1-p3-1).find("#")+p3+1;

        errs() << "BB_Offset: " << BB_Offset << "\n";
        //std::string Prefix = BB_Offset.substr(0, p0);
        //std::string BB_name = BB_Offset.substr(p0+1, p1-p0-1);
        int offset = std::stoi(BB_Offset.substr(p1+1,p2-p1-1));
        int index = BB_Offset[p2+1]-'0';
        long long target_val0 = std::stoll(BB_Offset.substr(p3+1, p4-p3-1));
        long long target_val1 = std::stoll(BB_Offset.substr(p4+1, p5-p4-1));
        int OpID = std::stoi(BB_Offset.substr(p5+1, BB_Offset.length()-p5-1));
        // CY_TEMP: when we only flip condition to cover both branches
        //if (OpID == 2)
        //    return;
        std::string tmp_str = BB_Offset.substr(0, p2);

        //errs() << Prefix << "\n";
        //errs() << "BB_name: " << BB_name << "\n";
        //errs() << "index: " << index << "\n";
        //errs() << "offset: " << offset << "\n";
        //errs() << "target_val1: " << target_val0 << "\n";
        //errs() << "target_val2: " << target_val1 << "\n";
        int count = 0;
        Instruction *target_I;
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
            if (count == offset){
                target_I = &(*II);
                break;
            }
        }
        if (count != offset){ //Should not happen
            errs() << "Count != Offset\n";
            errs() << "Count: " << count << "\n";
            errs() << "BB: " << BB->getName() << " offset: " << offset << "\n";
        }
        errs() << *target_I << "\n";
        Value *curOperand = target_I->getOperand(index);
        Type *CMPType = curOperand->getType();
        if (CMPType->isIntOrIntVectorTy()){
            if (isa<ConstantInt>(curOperand)){
                if (OpID == 0 || OpID == 1){ // ave -> x > min && x < max
                    errs() << "Constant|" << target_I->getParent()->getParent()->getName() << "|" << tmp_str << "|" << index << "#" << (target_val0+target_val1)/2 << "@0\n";
                }
                if (OpID == 0 || OpID == 2){ // max -> x >= max
                    errs() << "Constant|" << target_I->getParent()->getParent()->getName() << "|" << tmp_str << "|" << index << "#" << target_val0 << "@1\n";
                }
                if (OpID == 1 || OpID == 2){ // min -> x <= min
                    errs() << "Constant|" << target_I->getParent()->getParent()->getName() << "|" << tmp_str << "|" << index << "#" << target_val1 << "@2\n";
                }
            }
            else{
                //print target flipping result to v7
                errs() << BB_Offset << "\n";
            }
        }
        else{
            //TODO: print out to show the instruction is not int
        }
    }


    struct IsConstant : public ModulePass {
        static char ID;
        std::map<std::string, std::vector<std::string>>Target_BB;
		LLVMContext *context;
        IsConstant() : ModulePass(ID) {}
		
        unsigned Not_CMP_Count = 0, CMP_Count = 0;
		//const char *format = " CMP %d with %d\n";
		const char *format_ss = " CMP %lld with %lld\n";
		const char *format_uu = " CMP %llu with %llu\n";

        void File_Read(){
            std::string line;
            std::ifstream inFile("NEW_INPUT_v5.txt");
            Target_BB.clear();
            while (getline(inFile, line)){
                int p0 = line.find(","); //Previous we have File Prefix, not p0's value is -1, so p0+1 is still correct
                int p1 = line.rfind(":");
                std::string BB_name = line.substr(p0+1, p1-p0-1); 
                //int p2 = line.find("#");
                std::vector<std::string> new_vector;
                if (Target_BB.find(BB_name) == Target_BB.end())
                    Target_BB[BB_name] = new_vector;
                //Target_BB[BB_name].push_back(line.substr(p1+1, p2-p1-1));
                Target_BB[BB_name].push_back(line);
            }
            inFile.close();
        }

		bool doInitialization(Module &M) override {
            File_Read();
        }

        bool runOnModule(Module &M) override {
            for (auto &F: M)
                for (auto &B: F){
                    std::string tmp_name = B.getName();
                    if (tmp_name.find("b") == 0 && Target_BB.find(tmp_name) != Target_BB.end()){
                        for (std::vector<std::string>::iterator it = Target_BB[tmp_name].begin(), eit = Target_BB[tmp_name].end(); it != eit; it++){
                            findBBOffset(&B, *it);
                        }
                    }
                }

            return false;
        }
    };
}

char IsConstant::ID = 0;
static RegisterPass<IsConstant> X("IsConstant", "Instrumentation Pass for Model Checker", false, false);
