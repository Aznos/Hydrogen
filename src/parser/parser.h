#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "ast.h"
#include "../lexer/lexer.h"

FunctionNode* parseFunction();
void expectToken(TokenType expectedToken);

#endif