//==============================================================================
// FILE:
//    OpcodeCounter.h
//
// DESCRIPTION:
//    声明OpcodeCounter Pass：
//      * 新Pass Manager接口
//      * 新Pass Manager的打印Pass
//
// License: MIT
//==============================================================================
#ifndef LLVM_TUTOR_OPCODECOUNTER_H
#define LLVM_TUTOR_OPCODECOUNTER_H

#include "llvm/ADT/StringMap.h"  // 引入LLVM的字符串映射工具
#include "llvm/IR/Function.h"    // 引入LLVM中的函数表示
#include "llvm/IR/PassManager.h" // 引入新版Pass Manager的相关声明
#include "llvm/Pass.h"           // 引入Pass的基类
#include "llvm/Support/raw_ostream.h" // 引入LLVM的原始输出流工具

//------------------------------------------------------------------------------
// 新版Pass Manager接口
//------------------------------------------------------------------------------
using ResultOpcodeCounter = llvm::StringMap<unsigned>; // 定义一个字符串映射结果类型，映射操作码到它们的使用次数

// OpcodeCounter分析Pass类定义
struct OpcodeCounter : public llvm::AnalysisInfoMixin<OpcodeCounter> {
  using Result = ResultOpcodeCounter; // 使用ResultOpcodeCounter作为结果类型
  // 运行分析Pass的方法
  Result run(llvm::Function &F, llvm::FunctionAnalysisManager &);

  // 生成操作码映射的方法
  OpcodeCounter::Result generateOpcodeMap(llvm::Function &F);
  // 官方API的一部分，表明这个Pass是必须的
  static bool isRequired() { return true; }

private:
  // 一个特殊类型，由分析Pass使用，提供一个标识该分析Pass类型的地址
  static llvm::AnalysisKey Key;
  // 允许llvm::AnalysisInfoMixin访问Key
  friend struct llvm::AnalysisInfoMixin<OpcodeCounter>;
};

//------------------------------------------------------------------------------
// 新版Pass Manager打印Pass接口
//------------------------------------------------------------------------------
// OpcodeCounterPrinter打印Pass类定义
class OpcodeCounterPrinter : public llvm::PassInfoMixin<OpcodeCounterPrinter> {
public:
  // 构造函数，接受一个输出流
  explicit OpcodeCounterPrinter(llvm::raw_ostream &OutS) : OS(OutS) {}
  // 运行打印Pass的方法
  llvm::PreservedAnalyses run(llvm::Function &Func, llvm::FunctionAnalysisManager &FAM);
  // 官方API的一部分，表明这个Pass是必须的
  static bool isRequired() { return true; }

private:
  llvm::raw_ostream &OS; // 输出流引用，用于打印结果
};
#endif // LLVM_TUTOR_OPCODECOUNTER_H
