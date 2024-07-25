#ifndef AST_H
#define AST_H

#include "../lexer/lexer.h"
#include <string>
#include <memory>
#include <vector>

struct VariableNode {
    std::string type;
    std::string name;
    int value;
};

struct FunctionNode {
    std::string type;
    std::string functionName;
    std::vector<std::unique_ptr<VariableNode>> variables;
};

#endif