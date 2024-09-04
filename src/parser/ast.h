#ifndef AST_H
#define AST_H

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
#include "parser.h"
#include "codegen/codegen.h"

using namespace llvm;

class ExprAST { //Base class for all expression nodes
    public:
        virtual ~ExprAST() = default;
        virtual Value *codegen() = 0;
};

class NumberExprAST : public ExprAST { //Expression class for numeric literals
    double val;

    public:
        NumberExprAST(double val) : val(val) {}
        Value *codegen() override;
};

class VariableExprAST : public ExprAST { //Expression class for referencing a variable
    std::string name;

    public:
        VariableExprAST(const std::string &name) : name(name) {}
        Value *codegen() override;
};

class BinaryExprAST : public ExprAST { //Expression class for a binary operation
    char op; //Op code
    std::unique_ptr<ExprAST> LHS, RHS; //Left and right side of the equasion

    public:
        BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
        Value *codegen() override;
};

class CallExprAST : public ExprAST { //Expression class for function calls
    std::string callee; //What function the function was called from
    std::vector<std::unique_ptr<ExprAST> > args;

    public:
        CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST> > args) : callee(callee), args(std::move(args)) {}
        Value *codegen() override;
};

class PrototypeAST { //Represents a prototype for a function which takes a name and argument names
    std::string name;
    std::vector<std::string> args;

    public:
        PrototypeAST(const std::string &name, std::vector<std::string> args) : name(name), args(std::move(args)) {}
        Function *codegen();
        const std::string &getName() const {
            return name;
        }
};

class FunctionAST { //Represents a function definition
    std::unique_ptr<PrototypeAST> prototype;
    std::unique_ptr<ExprAST> body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body) : prototype(std::move(prototype)), body(std::move(body)) {}
        Function *codegen();
};


#endif