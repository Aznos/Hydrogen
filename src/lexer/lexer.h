#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_VOID,
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_EQUALS,
    TOKEN_NUMBER,
    TOKEN_PRINT,
    TOKEN_STRING_LITERAL,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

void initLexer(FILE* file);
TokenType nextToken();
TokenType readKeyword(char c);
TokenType readNumber(char c);
char getNextChar();
char* getCurrentTokenValue();
bool isWhitespace(char c);
bool isStringLiteral(char* word);

#endif