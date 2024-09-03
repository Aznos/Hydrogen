#ifndef PARSER_H
#define PARSER_H

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "ast.h"

extern int currentTok;
extern int getNextToken();

extern std::map<char, int> BinopPrecedence; //Holds precedence for each binary op thats defined
extern int getTokPrecedence(); //Get prededence of pending binop token

extern std::unique_ptr<ExprAST> logError(const char *str);

extern std::unique_ptr<ExprAST> parseExpression();
extern std::unique_ptr<ExprAST> parseNumberExpr();
extern std::unique_ptr<ExprAST> parseParenExpr(); //Parse '(' and ')'
extern std::unique_ptr<ExprAST> parseidentifierExpr();
extern std::unique_ptr<ExprAST> parsePrimary();
extern std::unique_ptr<ExprAST> parseBinopRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
extern std::unique_ptr<ExprAST> parseExpression();
extern std::unique_ptr<PrototypeAST> parsePrototype();
extern std::unique_ptr<FunctionAST> parseFunction(); //Parse 'fn'
extern std::unique_ptr<FunctionAST> parseTopLevelExpr();
extern std::unique_ptr<PrototypeAST> parseExtern();

extern void handleDefinition();
extern void handleExtern();
extern void handleTopLevelExpr();
extern void mainLoop();

#endif