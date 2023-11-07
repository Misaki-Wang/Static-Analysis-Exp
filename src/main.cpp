#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/Support/raw_ostream.h"

#include "llvmPass/include/Defpass.hpp" // 你的DefPass头文件

using namespace llvm;

/*
1. transfer the .c file to .ll(IR)
2. Use Pass to analyse the IR of tests
3. generate VarEmbedding
4. generate FuncEmbedding
5. calculate the similarity
6. cluster based on the similarity(based on Python?)
*/

int main(int argc, char **argv) {
    // 初始化LLVM上下文
    LLVMContext Context;
    SMDiagnostic Err;

    // 解析给定的LLVM IR文件
    std::unique_ptr<Module> Mod = parseIRFile("/tests/test1.ll", Err, Context);
    if (!Mod) {
        Err.print(argv[0], errs());
        return 1;
    }

    // 创建Pass管道
    PassBuilder PB;
    FunctionPassManager FPM;
    FPM.addPass(DefPass());

    // 运行Pass
    FPM.run(*Mod);

    // 输出分析结果
    // （这里假设你的DefPass已经打印了相关输出）
    // 如果你需要在这里打印结果，你需要从你的Pass中获取信息，例如通过全局变量或其它机制

    return 0;
}
