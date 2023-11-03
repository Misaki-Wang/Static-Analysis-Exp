#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include <set>

using namespace llvm;

namespace {
    struct CfuncPass : public FunctionPass {
        static char ID;

        CfuncPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            std::map<Value*, std::set<Function*>> variableToFunctions;

            // 遍历函数的所有基本块和指令
            for (auto &BB : F) {
                for (auto &I : BB) {
                    // 检查每个调用指令
                    if (CallInst *callInst = dyn_cast<CallInst>(&I)) {
                        for (unsigned i = 0; i < callInst->getNumOperands() - 1; i++) {
                            Value *arg = callInst->getOperand(i);
                            variableToFunctions[arg].insert(callInst->getCalledFunction());
                        }
                    }
                }
            }

            for (auto &entry : variableToFunctions) {
                Value *var = entry.first;
                std::set<Function*> &functions = entry.second;
                errs() << "Variable: " << var->getName() << " is passed to " << functions.size() << " distinct functions.\n";
            }

            return false;
        }
    };
}

char CfuncPass::ID = 0;
static RegisterPass<CfuncPass> X("CfuncPass", "Count Functions where Variable is Passed", false, false);
