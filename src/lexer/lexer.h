#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_VOID,
    TOKEN_IDENTIFIER,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_EOF
} TokenType;

TokenType nextToken();

#endif