#include "parser.h"
#include "../codegen/arm_codegen.h"

extern FILE* lexerFile;

FunctionNode* parseFunction() {
    FunctionNode* node = malloc(sizeof(FunctionNode));
    TokenType token;

    token = nextToken();
    if (token != TOKEN_VOID) {
        printf("ERR: Expected \"void\" in function declaration\n");
        free(node);
        return NULL;
    }
    node->type = "void";

    token = nextToken();
    if (token != TOKEN_IDENTIFIER || strcmp(getCurrentTokenValue(), "main") != 0) {
        printf("ERR: Expected \"main\" in function declaration\n");
        free(node);
        return NULL;
    }
    node->functionName = "main";

    token = nextToken();
    if (token != TOKEN_LEFT_PAREN) {
        printf("ERR: Expected \"(\"\n");
        free(node);
        return NULL;
    }

    token = nextToken();
    if (token != TOKEN_RIGHT_PAREN) {
        printf("ERR: Expected \")\"\n");
        free(node);
        return NULL;
    }

    token = nextToken();
    if (token != TOKEN_LEFT_BRACE) {
        printf("ERR: Expected \"{\" in function declaration\n");
        free(node);
        return NULL;
    }

    parseFunctionBody(node);

    token = nextToken();
    if (token != TOKEN_RIGHT_BRACE) {
        printf("ERR: Expected \"}\" in function declaration\n");
        free(node);
        return NULL;
    }

    return node;
}

void parseFunctionBody(FunctionNode* function) {
    TokenType token;
    while ((token = nextToken()) != TOKEN_RIGHT_BRACE) {
        if (token == TOKEN_INT) {
            VariableNode* var = parseVariableDeclaration();
            if (var) {
                var->next = function->variables;
                function->variables = var;
            }
        } else if(token == TOKEN_PRINT) {
            parsePrintStatement();
        } else {
            printf("ERR: Unexpected token in function body\n");
            break;
        }
    }

    ungetc('}', lexerFile);
}

VariableNode* parseVariableDeclaration() {
    VariableNode* node = malloc(sizeof(VariableNode));
    node->type = "int";
    node->next = NULL;

    TokenType token = nextToken();
    if (token != TOKEN_IDENTIFIER) {
        printf("ERR: Expected identifier in variable declaration\n");
        free(node);
        return NULL;
    }
    node->name = strdup(getCurrentTokenValue());

    token = nextToken();
    if (token != TOKEN_EQUALS) {
        printf("ERR: Expected \"=\" in variable declaration\n");
        free(node->name);
        free(node);
        return NULL;
    }

    token = nextToken();
    if (token != TOKEN_NUMBER) {
        printf("ERR: Expected number in variable declaration\n");
        free(node->name);
        free(node);
        return NULL;
    }
    node->value = atoi(getCurrentTokenValue());

    token = nextToken();
    if (token != TOKEN_SEMICOLON) {
        printf("ERR: Expected \";\" at the end of variable declaration\n");
        free(node->name);
        free(node);
        return NULL;
    }

    return node;
}

void parsePrintStatement() {
    if(nextToken() != TOKEN_LEFT_PAREN) {
        printf("ERR: Expected \"(\" in print statement\n");
        return;
    }

    TokenType token = nextToken();
    if(token == TOKEN_STRING_LITERAL) {
        char* str = getCurrentTokenValue();
        emitPrintString(str);
    } else if(token == TOKEN_IDENTIFIER) {
        char* varName = getCurrentTokenValue();
        emitPrintVariable(varName);
    } else {
        printf("ERR: Expected string literal or identifier in print statement\n");
        return;
    }

    if(nextToken() != TOKEN_RIGHT_PAREN) {
        printf("ERR: Expected \")\" in print statement\n");
    }
}