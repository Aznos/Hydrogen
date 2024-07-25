#include "parser.h"

FunctionNode* parseFunction() {
    FunctionNode* node = malloc(sizeof(FunctionNode));
    TokenType token;

    token = nextToken();
    if(token != TOKEN_VOID) {
        printf("ERR: Expected \"void\" in function declaration\n");
        free(node);
        return NULL;
    }
    node->type = "void";

    token = nextToken();
    if(token != TOKEN_IDENTIFIER) {
        printf("ERR: Expected \"main\" in function declaration\n");
        free(node);
        return NULL;
    }
    node->functionName = "main";

    token = nextToken();
    if(token != TOKEN_LEFT_PAREN) {
        printf("ERR: Expected \"(\"\n");
        free(node);
        return NULL;
    }

    token = nextToken();
    if(token != TOKEN_RIGHT_PAREN) {
        printf("ERR: Expected \")\"\n");
        free(node);
        return NULL;
    }

    parseFunctionBody();

    token = nextToken();
    if(token != TOKEN_LEFT_BRACE) {
        printf("ERR: Expected \"{\" in function declaration\n");
        free(node);
        return NULL;
    }

    token = nextToken();
    if(token != TOKEN_RIGHT_BRACE) {
        printf("ERR: Expected \"}\" in function declaration\n");
        free(node);
        return NULL;
    }

    return node;
}

void parseFunctionBody() {
    TokenType token;
    while((token = nextToken()) != TOKEN_RIGHT_BRACE) {
        if(token == TOKEN_INT) {
            VariableNode* var = parseVariableDeclaration();
            printf("Declared variable: %s of type %s with value %d\n", var->name, var->type, var->value);
        }
    }
}

VariableNode* parseVariableDeclaration() {
    VariableNode* node = malloc(sizeof(VariableNode));
    node->type = "int";

    TokenType token = nextToken();
    if(token != TOKEN_IDENTIFIER) {
        printf("ERR: Expected identifier in variable declaration\n");
        free(node);
        return NULL;
    }
    node->name = strdup(getCurrentTokenValue());

    token = nextToken();
    if(token != TOKEN_EQUALS) {
        printf("ERR: Expected \"=\" in variable declaration\n");
        free(node);
        return NULL;
    }

    token = nextToken();
    if(token != TOKEN_NUMBER) {
        printf("ERR: Expected number in variable declaration\n");
        free(node);
        return NULL;
    }
    node->value = atoi(getCurrentTokenValue());

    token = nextToken();
    if(token != TOKEN_SEMICOLON) {
        printf("ERR: Expected \";\" in variable declaration\n");
        free(node);
        return NULL;
    }

    return node;
}