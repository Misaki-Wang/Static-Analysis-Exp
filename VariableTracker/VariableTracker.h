//==============================================================================
// FILE:
//    VariableTracker.h
//
// DESCRIPTION:
//    声明VariableTracker Pass：
//      * 新Pass Manager接口
//      * 新Pass Manager的打印Pass
//
// License: MIT
//==============================================================================
#ifndef LLVM_TUTOR_VARIABLETRACKER_H
#define LLVM_TUTOR_VARIABLETRACKER_H

#include "llvm/ADT/StringMap.h"  // 引入LLVM的字符串映射工具
#include "llvm/IR/Function.h"    // 引入LLVM中的函数表示
#include "llvm/IR/PassManager.h" // 引入新版Pass Manager的相关声明
#include "llvm/Pass.h"           // 引入Pass的基类
#include "llvm/Support/raw_ostream.h" // 引入LLVM的原始输出流工具
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Casting.h"

#include <map>
#include <set>

//------------------------------------------------------------------------------
// 新版Pass Manager接口
//------------------------------------------------------------------------------
struct VariableInfo {
  int Def = 0;
  int Use = 0;
  std::set<llvm::Value*> Ptrs;
  std::set<llvm::Function*> Cfunc;
  std::set<llvm::Value*> Dvars;
};

// 定义一个映射结果类型，映射每个变量到它的信息
using ResultVariableTracker = std::map<llvm::Value*, VariableInfo>;

// VariableTracker分析Pass类定义
class VariableTracker : public llvm::AnalysisInfoMixin<VariableTracker> {
public:
  using Result = ResultVariableTracker; // 使用ResultVariableTracker作为结果类型
  // 运行分析Pass的方法
  Result run(llvm::Function &F, llvm::FunctionAnalysisManager &);

  // 生成映射的方法
  VariableTracker::Result generateVariableMap(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

  // 官方API的一部分，表明这个Pass是必须的
  static bool isRequired() { return true; }

private:
  // 一个特殊类型，由分析Pass使用，提供一个标识该分析Pass类型的地址
  static llvm::AnalysisKey Key;
  // 允许llvm::AnalysisInfoMixin访问Key
  friend struct llvm::AnalysisInfoMixin<VariableTracker>;
};

//------------------------------------------------------------------------------
// 新版Pass Manager打印Pass接口
//------------------------------------------------------------------------------
// VariableTrackerPrinter打印Pass类定义
class VariableTrackerPrinter : public llvm::PassInfoMixin<VariableTrackerPrinter> {
public:
  // 构造函数，接受一个输出流
  explicit VariableTrackerPrinter(llvm::raw_ostream &OutS) : OS(OutS) {}
  // 运行打印Pass的方法
  llvm::PreservedAnalyses run(llvm::Function &Func, llvm::FunctionAnalysisManager &FAM);
  // 官方API的一部分，表明这个Pass是必须的
  static bool isRequired() { return true; }

private:
  llvm::raw_ostream &OS; // 输出流引用，用于打印结果
};

#endif // LLVM_TUTOR_VARIABLETRACKER_H
