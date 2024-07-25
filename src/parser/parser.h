#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include "ast.h"
#include "../lexer/lexer.h"

void parseFunctionBody(FunctionNode& function);
std::unique_ptr<FunctionNode> parseFunction();
std::unique_ptr<VariableNode> parseVariableDeclaration();

#endif