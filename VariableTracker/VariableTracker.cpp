// VariableTracker.cpp - 分析和打印函数中变量的使用情况

#include "VariableTracker.h" // 引入VariableTracker的声明

#include "llvm/IR/LegacyPassManager.h"  // 引入LLVM旧版PassManager
#include "llvm/Passes/PassBuilder.h"    // 引入用于构建新版PM的PassBuilder
#include "llvm/Passes/PassPlugin.h"     // 引入用于插件注册的PassPlugin库

using namespace llvm; // 使用llvm命名空间

// 函数声明：打印变量跟踪结果
static void printVariableTrackerResult(llvm::raw_ostream &, const std::map<llvm::Value*, VariableInfo> &Vars);


//-----------------------------------------------------------------------------
// VariableTrackerPass实现部分
//-----------------------------------------------------------------------------
AnalysisKey VariableTracker::Key; // 创建一个全局分析密钥

// 生成映射的函数
VariableTracker::Result VariableTracker::generateVariableMap(Function &F, FunctionAnalysisManager &FAM){
    // 首先，获取Alias Analysis的结果
    auto &AA = FAM.getResult<llvm::AAManager>(F);

    // 为每个变量初始化计数器
    std::map<llvm::Value*, VariableInfo> variables;

    // 遍历函数中的所有基本块和指令
    for (auto &BB : F) {
      for (auto &Inst : BB) {

        // 检查指令是否是变量分配或存储 Def
        if (auto *Alloca = llvm::dyn_cast<llvm::AllocaInst>(&Inst)) {
          // 如果是变量分配，增加Def计数
          variables[Alloca].Def++;
        } else if (auto *Store = llvm::dyn_cast<llvm::StoreInst>(&Inst)) {
          // 如果是变量存储，增加Def计数
          llvm::Value *Ptr = Store->getPointerOperand();
          variables[Ptr].Def++;
        }

        // 检查指令的每个操作数 USE
        for (llvm::Value *Operand : Inst.operands()) {
          if (variables.count(Operand)) {
            // 如果操作数是追踪的变量，增加Use计数
            variables[Operand].Use++;
          }
        }

        // 如果指令是函数调用 Cfunc 
        if (auto *Call = llvm::dyn_cast<llvm::CallInst>(&Inst)) {
            // 遍历所有调用的参数
            for (auto &Arg : Call->args()) {
                llvm::Value *ActualArg = Arg.get();
                // 如果参数是我们追踪的变量之一
                if (variables.count(ActualArg)) {
                // 获取该变量的信息
                VariableInfo &VarInfo = variables[ActualArg];
                // 获取调用的函数
                llvm::Function *Callee = Call->getCalledFunction();
                if (Callee) {
                    // 如果调用的是直接函数（有明确的函数名），增加Cfunc计数
                    VarInfo.Cfunc.insert(Callee);
                } 
                // TODO: ptr analysis  
                // else {
                //     // 如果调用的是间接函数（通过指针调用），这里需要进一步分析
                //     // 可能需要利用其他的分析结果，例如：指针分析
                // }
                }
            }
        }

        // 进行Alias Analysis，更新Ptrs集合
        for (auto &VarInfoPair : variables) {
          llvm::Value *Var = VarInfoPair.first;  // 变量的指针
          for (llvm::Value *Operand : Inst.operands()) {
            if (AA.isMustAlias(Var, Operand)) {
            // 如果当前的变量Var和操作数Operand之间存在必须别名关系，
            // 即Var和Operand引用的内存位置是相同的，那么执行以下操作
              VarInfoPair.second.Ptrs.insert(Operand); // 将操作数添加到变量的别名集合中
            }
          }
        }

        // 分析Dvars 
        for (auto &VarInfoPair : variables) { // 遍历所有的变量及其统计信息
          llvm::Value *Var = VarInfoPair.first; // 获取当前变量
          for (llvm::User *U : Var->users()) {  // 遍历当前变量的所有用户，即所有使用该变量的指令
            if (llvm::Instruction *UserInst = llvm::dyn_cast<llvm::Instruction>(U)) { // 尝试将用户转换为指令，如果成功，说明这个用户是一条指令
              if (UserInst->getFunction() == &F) {  // 检查这条指令是否属于当前分析的函数F
                VarInfoPair.second.Dvars.insert(UserInst);  // 如果是，将这条指令添加到当前变量的依赖变量集合Dvars中
              }
            }
          }
        }


      }
    }
    return variables;
}

// 运行变量跟踪分析pass的函数
VariableTracker::Result VariableTracker::run(Function &F, FunctionAnalysisManager &FAM){ 
  // 收集和返回分析结果
  return generateVariableMap(F, FAM);
}  

// 运行VariableTrackerPrinter打印Pass的函数
PreservedAnalyses VariableTrackerPrinter::run(Function &F, FunctionAnalysisManager &FAM) {
  // 我们需要从分析管理器中获取VariableTrackerPass的结果
  auto &Vars = FAM.getResult<VariableTracker>(F);

  // 打印分析的标题信息
  OS << "Printing analysis 'VariableTracker Pass' for function '" << F.getName() << "':\n";

  // 调用之前定义的辅助函数来打印变量追踪s的结果
  printVariableTrackerResult(OS, Vars);

  // 返回一个标记，表示所有分析都得到了保留
  return PreservedAnalyses::all();
}


// 新版PM注册部分
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getVariableTrackerPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "VariableTracker", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      // 注册回调以添加pass

      // #1 注册print<variable-tracker>，使其能通过-passes=在命令行中使用
      PB.registerPipelineParsingCallback(
          [&](StringRef Name, FunctionPassManager &FPM,
              ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "VariableTracker") {
              FPM.addPass(VariableTrackerPrinter(llvm::errs()));
              return true;
            }
            return false;
          });

      // #2 注册优化级别，当使用-O{1|2|3|s}时作为现有管道的一部分执行
      PB.registerVectorizerStartEPCallback(
          [](llvm::FunctionPassManager &PM, llvm::OptimizationLevel Level) {
            PM.addPass(VariableTrackerPrinter(llvm::errs()));
          });

      // #3 注册VariableTracker作为一个分析pass，这样它就可以被VariableTrackerPrinter（或其他pass）请求其结果
      PB.registerAnalysisRegistrationCallback(
          [](FunctionAnalysisManager &FAM) {
            FAM.registerPass([&] { return VariableTracker(); });
          });
      }
  };
}

// 注册插件
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getVariableTrackerPluginInfo();
}


//------------------------------------------------------------------------------
// Helper functions - implementation
//------------------------------------------------------------------------------
static void printVariableTrackerResult(llvm::raw_ostream &OutS, 
                                       const std::map<llvm::Value*, VariableInfo> &Vars) {
  OutS << "======================================================================\n";
  OutS << "Static-Analysis: VariableTracker results\n";
  OutS << "======================================================================\n";
  const char *str1 = "VARIABLE";
  const char *str2 = "DEF";
  const char *str3 = "USE";
  const char *str4 = "PTRS";
  const char *str5 = "CFUNC";
  const char *str6 = "DVARS";
  OutS << format("%-20s %-10s %-10s %-10s %-10s %-10s\n", 
                  str1, str2, str3, str4, str5, str6);
  OutS << "----------------------------------------------------------------------\n";

  for (const auto &VarPair : Vars) {
    const llvm::Value *Var = VarPair.first;
    const VariableInfo &Info = VarPair.second;
    OutS << format("%-20s %-10d %-10d %-10lu %-10lu %-10lu\n", 
                    Var->getName().str().c_str(),
                    Info.Def, Info.Use, Info.Ptrs.size(), Info.Cfunc.size(), Info.Dvars.size());
  }

  OutS << "-----------------------------------------------------------------------\n\n";
}
