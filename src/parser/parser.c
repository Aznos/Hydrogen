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

    token = nextToken();
    if(token != TOKEN_LEFT_BRACE) {
        printf("ERR: Expected \"{\" in function declaration\n");
        free(node);
        return NULL;
    }

    //Parse body..

    token = nextToken();
    if(token != TOKEN_RIGHT_BRACE) {
        printf("ERR: Expected \"}\" in function declaration\n");
        free(node);
        return NULL;
    }

    return node;
}