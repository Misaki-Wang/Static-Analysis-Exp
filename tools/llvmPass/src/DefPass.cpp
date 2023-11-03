// DefPass.cpp
#include "include/Defpass.hpp"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

char DefPass::ID = 0;

DefPass::DefPass() : FunctionPass(ID) {}

bool DefPass::runOnFunction(Function &F) {
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

static RegisterPass<DefPass> X("DefPass", "Extract Def Values", false, false);
