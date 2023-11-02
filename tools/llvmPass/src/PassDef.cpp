#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct DefPass : public FunctionPass {
    static char ID;
    DefPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      errs() << "Analyzing function: " << F.getName() << "\n";

      for (BasicBlock &BB : F) {
        for (Instruction &I : BB) {
          // Check for instructions that define a value
          if (isa<AllocaInst>(&I) || isa<StoreInst>(&I)) {
            if (isa<AllocaInst>(&I)) {
              errs() << "Variable Allocated: " << I << "\n";
            } 
            else if (isa<StoreInst>(&I)) {
              errs() << "Variable Defined: " << I << "\n";
            }
          }
        }
      }

      return false; // No modifications to the input IR
    }
  };
}

char DefPass::ID = 0;
static RegisterPass<DefPass> X("DefPass", "Extract Def Values", false, false);
