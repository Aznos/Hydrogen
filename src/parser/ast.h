#ifndef AST_H
#define AST_H

#include "../lexer/lexer.h"

typedef struct {
    char* type;
    char* functionName;
    VariableNode* variables;
} FunctionNode;

typedef struct {
    char* type;
    char* name;
    int value;
    struct VariableNode* next;
} VariableNode;

#endif