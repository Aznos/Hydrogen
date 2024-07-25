#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <stdio.h>
#include <stddef.h>
#include "../parser/ast.h"

void generateLLVMIR(FunctionNode* function, const char* outputFile);

#endif