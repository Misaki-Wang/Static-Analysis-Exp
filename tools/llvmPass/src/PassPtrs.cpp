#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct UsePass : public FunctionPass {
        static char ID;

        UsePass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            // 遍历函数中的每一个基本块
            for (auto &BB : F) {
                // 遍历基本块中的每一条指令
                for (auto &I : BB) {
                    // 如果这条指令是一个Load指令，那么它使用了一个变量
                    if (isa<LoadInst>(&I)) {
                        // 获取该指令使用的变量名
                        Value *usedVar = dyn_cast<LoadInst>(&I)->getPointerOperand();
                        // 打印出使用的变量名
                        errs() << "Variable used: " << usedVar->getName() << "\n";
                    }
                }
            }
            return false; // 返回false表示这个pass没有修改IR
        }
    };
}

char UsePass::ID = 0;
static RegisterPass<UsePass> X("UsePass", "Count Use Values", false, false);
