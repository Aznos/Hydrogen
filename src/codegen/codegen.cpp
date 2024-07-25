#include "codegen.h"
#include "../parser/ast.h"

void generateLLVMIR(FunctionNode* function, const char* outputFileName) {
    llvm::LLVMContext Context;
    llvm::Module* Module = new llvm::Module("main", Context);
    llvm::IRBuilder<> Builder(Context);

    llvm::FunctionType* FuncType = llvm::FunctionType::get(Builder.getVoidTy(), false);
    llvm::Function* MainFunc = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "main", Module);

    llvm::BasicBlock* Entry = llvm::BasicBlock::Create(Context, "entry", MainFunc);
    Builder.SetInsertPoint(Entry);

    VariableNode* var = function->variables;
    while(var != NULL) {
        llvm::Value* VarAlloc = Builder.CreateAlloca(Builder.getInt32Ty(), nullptr, var->name);
        Builder.CreateStore(Builder.getInt32(var->value), VarAlloc);

        var = var->next;
    }

    Builder.CreateRetVoid();
    llvm::verifyFunction(*MainFunc);

    std::error_code EC;
    llvm::raw_fd_ostream OS(outputFileName, EC, llvm::sys::fs::OF_None);
    Module->print(OS, nullptr);

    delete Module;
}