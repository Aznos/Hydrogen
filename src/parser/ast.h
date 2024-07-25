#ifndef AST_H
#define AST_H

#include "../lexer/lexer.h"

typedef struct {
    char* type;
    char* functionName;
} FunctionNode;

typedef struct {
    char* type;
    char* name;
    int value;
} VariableNode;

#endif