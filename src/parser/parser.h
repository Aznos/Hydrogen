#ifndef PARSER_H
#define PARSER_H

#include "main.h"
#include "ast.h"
#include "lexer/lexer.h"

static int currentTok;
static std::map<char, int> BinopPrecedence;

extern std::unique_ptr<ExprAST> logError(const char *str);
extern std::unique_ptr<PrototypeAST> logErrorP(const char *str);

extern std::unique_ptr<ExprAST> parseExpression();
extern std::unique_ptr<ExprAST> parseNumberExpr();
extern std::unique_ptr<ExprAST> parseParenExpr(); // Parse '(' and ')'
extern std::unique_ptr<ExprAST> parseidentifierExpr();
extern std::unique_ptr<ExprAST> parsePrimary();
extern std::unique_ptr<ExprAST> parseBinopRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);

extern std::unique_ptr<PrototypeAST> parsePrototype();
extern std::unique_ptr<FunctionAST> parseFunction(); // Parse 'fn'
extern std::unique_ptr<FunctionAST> parseTopLevelExpr();
extern std::unique_ptr<PrototypeAST> parseExtern();

int getNextToken();

// Additional function declarations
extern void handleFunction();
extern void handleExtern();
extern void handleTopLevelExpr();
extern void mainLoop();

#endif