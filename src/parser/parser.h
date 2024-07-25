#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "ast.h"
#include "../lexer/lexer.h"

void parseFunctionBody(FunctionNode* function);
FunctionNode* parseFunction();
VariableNode* parseVariableDeclaration();
void parsePrintStatement();

#endif