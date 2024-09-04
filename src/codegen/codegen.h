#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser/ast.h"  // Include ast.h first to ensure ExprAST is defined
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "main.h"
#include "parser/parser.h"
#include "lexer/lexer.h"

using namespace llvm;

extern std::unique_ptr<LLVMContext> context;
extern std::unique_ptr<Module> module;
extern std::unique_ptr<IRBuilder<>> builder;
extern std::map<std::string, Value*> namedValues;

Value *logErrorV(const char *str);

#endif