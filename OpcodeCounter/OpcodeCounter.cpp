// 这是LLVM的OpcodeCounter示例，它统计在LLVM IR中每个操作码的使用次数，并将结果打印到stderr。
// 下面的代码展示了如何将你的pass插入到预定义的扩展点，例如在任何其他转换之前运行它
// （例如通过Legacy PM的`EP_EarlyAsPossible`）或者在运行向量化器时（例如通过
// 新PM的`registerVectorizerStartEPCallback`）。

#include "OpcodeCounter.h" // 引入OpcodeCounter的声明

#include "llvm/IR/LegacyPassManager.h"  // 引入LLVM旧版PassManager
#include "llvm/Passes/PassBuilder.h"    // 引入用于构建新版PM的PassBuilder
#include "llvm/Passes/PassPlugin.h"     // 引入用于插件注册的PassPlugin库

using namespace llvm; // 使用llvm命名空间

// 函数声明：打印分析结果
static void printOpcodeCounterResult(llvm::raw_ostream &, const ResultOpcodeCounter &OC);

//-----------------------------------------------------------------------------
// OpcodeCounter实现部分
//-----------------------------------------------------------------------------
llvm::AnalysisKey OpcodeCounter::Key; // 创建一个全局分析密钥

// 生成操作码映射的函数
OpcodeCounter::Result OpcodeCounter::generateOpcodeMap(llvm::Function &Func) {
  OpcodeCounter::Result OpcodeMap; // 创建一个用于保存结果的映射

  // 遍历函数中的所有基本块和指令
  for (auto &BB : Func) {
    for (auto &Inst : BB) {
      StringRef Name = Inst.getOpcodeName(); // 获取操作码的名称

      // 如果映射中没有该操作码，初始化计数为1；否则增加计数
      if (OpcodeMap.find(Name) == OpcodeMap.end()) {
        OpcodeMap[Inst.getOpcodeName()] = 1;
      } else {
        OpcodeMap[Inst.getOpcodeName()]++;
      }
    }
  }

  return OpcodeMap; // 返回映射
}

// 运行分析pass的函数
OpcodeCounter::Result OpcodeCounter::run(llvm::Function &Func, llvm::FunctionAnalysisManager &) {
  return generateOpcodeMap(Func); // 生成并返回操作码映射
}

// 运行打印pass的函数
PreservedAnalyses OpcodeCounterPrinter::run(Function &Func, FunctionAnalysisManager &FAM) {
  auto &OpcodeMap = FAM.getResult<OpcodeCounter>(Func); // 从分析管理器中获取OpcodeCounter的结果

  // 打印分析的标题信息
  OS << "Printing analysis 'OpcodeCounter Pass' for function '" << Func.getName() << "':\n";

  printOpcodeCounterResult(OS, OpcodeMap); // 打印分析结果
  return PreservedAnalyses::all(); // 返回一个标记，表示所有分析都得到了保留
}

//-----------------------------------------------------------------------------
// 新版PM注册部分
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getOpcodeCounterPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "OpcodeCounter", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      // 注册回调以添加pass

      // #1 注册print<opcode-counter>，使其能通过-passes=在命令行中使用
      PB.registerPipelineParsingCallback(
          [&](StringRef Name, FunctionPassManager &FPM,
              ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "print<opcode-counter>") {
              FPM.addPass(OpcodeCounterPrinter(llvm::errs()));
              return true;
            }
            return false;
          });

      // #2 注册优化级别，当使用-O{1|2|3|s}时作为现有管道的一部分执行
      PB.registerVectorizerStartEPCallback(
          [](llvm::FunctionPassManager &PM, llvm::OptimizationLevel Level) {
            PM.addPass(OpcodeCounterPrinter(llvm::errs()));
          });

      // #3 注册OpcodeCounter作为一个分析pass，这样它就可以被OpcodeCounterPrinter（或其他pass）请求其结果
      PB.registerAnalysisRegistrationCallback(
          [](FunctionAnalysisManager &FAM) {
            FAM.registerPass([&] { return OpcodeCounter(); });
          });
      }
  };
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getOpcodeCounterPluginInfo();
}

//------------------------------------------------------------------------------
// Helper functions - implementation
//------------------------------------------------------------------------------
static void printOpcodeCounterResult(raw_ostream &OutS,
                                     const ResultOpcodeCounter &OpcodeMap) {
  OutS << "================================================="
               << "\n";
  OutS << "Static-Analysis: OpcodeCounter results\n";
  OutS << "=================================================\n";
  const char *str1 = "OPCODE";
  const char *str2 = "#TIMES USED";
  OutS << format("%-20s %-10s\n", str1, str2);
  OutS << "-------------------------------------------------"
               << "\n";
  for (auto &Inst : OpcodeMap) {
    OutS << format("%-20s %-10lu\n", Inst.first().str().c_str(),
                           Inst.second);
  }
  OutS << "-------------------------------------------------"
               << "\n\n";
}
