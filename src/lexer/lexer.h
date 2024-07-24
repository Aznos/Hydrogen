#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_VOID,
    TOKEN_IDENTIFIER,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_EOF
} TokenType;

void initLexer(FILE* file);
TokenType nextToken();
char getNextChar();
char* readKeyword(char c);
bool isWhitespace(char c);

#endif