// DefPass.hpp
#pragma once 

#include "llvm/Pass.h" // 包含LLVM Pass的头文件
#include "llvm/IR/Function.h" // 包含LLVM中Function类的头文件

namespace llvm {
  // 定义一个名为DefPass的结构体，它继承自FunctionPass，
  struct DefPass : public FunctionPass {
    static char ID; // 声明一个静态成员变量ID，用于唯一标识这个Pass
    DefPass(); // 声明构造函数
    bool runOnFunction(Function &F) override; // 声明runOnFunction方法，用于在函数上运行Pass
  };
}
