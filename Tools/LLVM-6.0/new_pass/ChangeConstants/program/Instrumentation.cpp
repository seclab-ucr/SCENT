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
#include <set>
#include <map>
#include <fstream>

#include "llvm/ADT/StringExtras.h"

#define Option1 false
using namespace llvm;
using namespace std;

namespace {

    struct changeConstants : public ModulePass {
        static char ID;
		LLVMContext *context;
        changeConstants() : ModulePass(ID) {}
            
		std::map<string,int>modify_target;
        std::set<string>modifed_target;


        bool runOnModule(Module &M0) {
			Module *M = &M0; //F.getParent();
			context = &M->getContext();
			
            std::set<int> tmp;
            string line;
            ifstream inFile("FLIP.txt");
            std::string Prefix;
            std::string value_str;
            int value;
            GlobalVariable *GV;
            unsigned BitWidth;
            Constant* const_int_val;
            while (getline(inFile, line)){
                int p0 = line.rfind("#");
                Prefix = line.substr(0, p0);
                value_str = line.substr(p0+1, line.size()-p0-1);
                errs() << "Value str: " << value_str << "\n";
                value = std::stoi(value_str);

                errs() << Prefix << " Value: " << value << "\n";
                /*
                if (global_name.find("getelementptr") == -1) //Global Variable
                {
                    //GV = M->getNamedValue(global_name); 
                    GV = M->getGlobalVariable(global_name);

                    BitWidth = (cast<IntegerType>(GV->getType()->getPointerElementType()))->getBitWidth();
                    const_int_val = ConstantInt::get(Type::getIntNTy(*context, BitWidth), value);
                    GV->setInitializer(const_int_val);
                    errs() << "Success\n";
                }
                else{
                    modify_target.insert({global_name, value});
                }
                */
            }
            inFile.close();

            //Prefix formate: Constant|Function|File:../Source_Code/Model0_tcp_input.h,b403:11|1#5#5
            int pos0 = Prefix.find("|"); //Constant
            int pos1 = Prefix.find("|", pos0+1);
            int pos2 = Prefix.find("|", pos1+1);

            std::string function_name = Prefix.substr(pos0+1, pos1-pos0-1);
            errs() << "Function_name: " << function_name << "\n";
            std::string bb_tmp = Prefix.substr(pos1+1, pos2-pos1-1);
            errs() << "BB_TMP: " << bb_tmp << "\n";
            int pos3 = bb_tmp.find(",");
            std::string bb_info = bb_tmp.substr(pos3+1, bb_tmp.length()-pos3-1);
            errs() << "bb_info: " << bb_info << "\n";
            int pos4 = bb_info.find(":");
            std::string bb_name = bb_info.substr(0,pos4);
            errs() << "bb_name: " << bb_name << "\n";
            int offset = std::stoi(bb_info.substr(pos4+1, bb_info.size()-pos4-1));
            errs() << "BB_Name: " << bb_name << "| Offset: " << offset << "\n";
            //std::string Op_index = substr(pos2+1,1);
            int target_index = Prefix[pos2+1]-'0';
            errs() << "target_index: " << target_index << "\n";
            int new_target = value;

            
            errs() << "M0_F: " << function_name << "\n";
            Function *M0_F = M->getFunction(function_name);
            std::string Model1_function_name(function_name);
            int pos;
            if (function_name.find("Model0") != -1){ //Model0
                while ((pos = Model1_function_name.find("Model0")) != -1){
                    Model1_function_name.replace(pos, 6, "Model1");
                }
                errs() << "M1_F: " << Model1_function_name << "\n";
            }
            else{
                while ((pos = Model1_function_name.find("Model1")) != -1){
                    Model1_function_name.replace(pos, 6, "Model0");
                }
                errs() << "M1_F: " << Model1_function_name << "\n";
            }
            Function *M1_F = M->getFunction(Model1_function_name);
           
            int count = 0;
            
            for (Function::iterator M0_BB = M0_F->begin(), M1_BB = M1_F->begin(); M0_BB != M0_F->end() && M1_BB != M1_F->end(); M0_BB++, M1_BB++){
                if (M0_BB->getName() != bb_name)
                    continue;
                for (BasicBlock::iterator M0_I = M0_BB->begin(), M1_I = M1_BB->begin(); M0_I != M0_BB->end() && M1_I != M1_BB->end(); M0_I++, M1_I++){
                    if (IntrinsicInst *ii = dyn_cast<IntrinsicInst>(&*M0_I)){
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
                    else if ((*M0_I).getName().startswith("CY_INST"))
                        count--;
                    else if (CallInst *CI = dyn_cast<CallInst>(M0_I)){
                        if (CI->isInlineAsm())
                            count--;
                    }
                    count++;
                    if (count == offset){
                        errs() << "M0_BB: " << M0_BB->getName() << "\n";
                        errs() << "M1_BB: " << M1_BB->getName() << "\n";
                        errs() << *M0_I << "\n";
                        errs() << *M1_I << "\n";
                        Value *M0_curOperand = M0_I->getOperand(target_index);
                        Type *CMPType = M0_curOperand->getType();
                        Constant *TMP = ConstantInt::get(CMPType, new_target);
                        M0_I->setOperand(target_index, TMP);
                        M1_I->setOperand(target_index, TMP);
                        errs() << "Success\n";
                        return true;
                    }
                }
            }
           
            errs() << "Not Matched\n";
            errs() << offset << "\n";
            return false;
        }
    };
}

char changeConstants::ID = 0;
static RegisterPass<changeConstants> X("changeConstants", "Instrumentation Pass for Model Checker", false, false);
