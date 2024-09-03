#ifndef AST_H
#define AST_H

#include "main.h"

namespace {
    class ExprAST { //Base class for all expression nodes
        public:
            virtual ~ExprAST() = default;
    };

    class NumberExprAST : public ExprAST { //Expression class for numeric literals
        double val;

        public:
            NumberExprAST(double val) : val(val) {}
    };

    class VariableExprAST : public ExprAST { //Expression class for referencing a variable
        std::string name;

        public:
            VariableExprAST(const std::string &name) : name(name) {}
    };

    class BinaryExprAST : public ExprAST { //Expression class for a binary operation
        char op; //Op code
        std::unique_ptr<ExprAST> LHS, RHS; //Left and right side of the equasion

        public:
            BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    };

    class CallExprAST : public ExprAST { //Expression class for function calls
        std::string callee; //What function the function was called from
        std::vector<std::unique_ptr<ExprAST> > args;

        public:
            CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST> > args) : callee(callee), args(std::move(args)) {}
    };

    class PrototypeAST { //Represents a prototype for a function which takes a name and argument names
        std::string name;
        std::vector<std::string> args;

        public:
            PrototypeAST(const std::string &name, std::vector<std::string> args) : name(name), args(std::move(args)) {}
            const std::string &getName() const {
                return name;
            }
    };

    class FunctionAST { //Represents a function definition
        std::unique_ptr<PrototypeAST> prototype;
        std::unique_ptr<ExprAST> body;

        public:
            FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body) : prototype(std::move(prototype)), body(std::move(body)) {}
    };
}

#endif