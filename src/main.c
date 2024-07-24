#include <stdio.h>
#include "lexer/lexer.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: ./hydrogen <filename>\n");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("File not found: %s\n", argv[1]);
        return 1;
    }

    initLexer(file);
    TokenType token;
    while((token = nextToken()) != TOKEN_EOF) {
        switch(token) {
            case TOKEN_VOID:
                printf("TOKEN_VOID\n");
                break;
            case TOKEN_IDENTIFIER:
                printf("TOKEN_IDENTIFIER\n");
                break;
            case TOKEN_LEFT_PAREN:
                printf("TOKEN_LEFT_PAREN\n");
                break;
            case TOKEN_RIGHT_PAREN:
                printf("TOKEN_RIGHT_PAREN\n");
                break;
            case TOKEN_LEFT_BRACE:
                printf("TOKEN_LEFT_BRACE\n");
                break;
            case TOKEN_RIGHT_BRACE:
                printf("TOKEN_RIGHT_BRACE\n");
                break;
            case TOKEN_EOF:
                printf("TOKEN_EOF\n");
                break;
        }
    }

    fclose(file);
}