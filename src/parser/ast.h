#ifndef AST_H
#define AST_H

#include "../lexer/lexer.h"

typedef struct {
    TokenType type;
    char* functionName;
} FunctionNode;

typedef struct {
    TokenType type;
    char* name;
} VariableNode;

#endif