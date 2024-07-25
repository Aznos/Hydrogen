#ifndef AST_H
#define AST_H

#include "../lexer/lexer.h"

struct VariableNode;
struct FunctionNode;

typedef struct VariableNode {
    char* type;
    char* name;
    int value;
    struct VariableNode* next;
} VariableNode;

typedef struct FunctionNode {
    char* type;
    char* functionName;
    VariableNode* variables;
} FunctionNode;

#endif