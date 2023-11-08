#ifndef VARIABLETRACKER_H
#define VARIABLETRACKER_H

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

struct VariableInfo {
  int Def = 0;
  int Use = 0;
  std::set<llvm::Value*> Ptrs;
  std::set<llvm::Function*> Cfunc;
  std::set<llvm::Value*> Dvars;
};

class VariableTrackerPass : public llvm::PassInfoMixin<VariableTrackerPass> {
public:
  using Result = std::map<llvm::Value*, VariableInfo>; // 使用Result作为结果类型

  // 运行分析Pass的方法
  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
  

  
  // 官方API的一部分，表明这个Pass是必须的
  static bool isRequired() { return true; }

private:
  // 一个特殊类型，由分析Pass使用，提供一个标识该分析Pass类型的地址
  static llvm::AnalysisKey Key;
  // 允许llvm::AnalysisInfoMixin访问Key
  friend struct llvm::AnalysisInfoMixin<VariableTrackerPass>;
};


// VariableTrackerPass的AnalysisKey定义
llvm::AnalysisKey VariableTrackerPass::Key;


// 新版Pass Manager的打印Pass定义
class VariableTrackerPrinter : public llvm::PassInfoMixin<VariableTrackerPrinter> {
public:
  explicit VariableTrackerPrinter(llvm::raw_ostream &OutS) : OS(OutS) {}

  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

  // 官方API的一部分，表明这个Pass是必须的
  static bool isRequired() { return true; }

private:
  llvm::raw_ostream &OS;
};

#endif // VARIABLETRACKER_H