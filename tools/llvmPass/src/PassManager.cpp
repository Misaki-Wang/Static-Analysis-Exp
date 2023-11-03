#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"

// 包含你的Pass头文件
#include "DefPass.h"
#include "UsePass.h"
#include "PtrsPass.h"
#include "CfuncPass.h"
#include "DvarsPass.h"

void runAllPassesOnModule(llvm::Module &module) {
    llvm::legacy::FunctionPassManager passManager(&module);
    
    // 添加你的Pass到PassManager
    passManager.add(new DefPass());
    passManager.add(new UsePass());
    passManager.add(new PtrsPass());
    passManager.add(new CfuncPass());
    passManager.add(new DvarsPass());
    
    // 执行所有的Pass
    passManager.run(module);
}
