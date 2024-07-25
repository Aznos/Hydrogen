#include "lexer.h"

FILE* lexerFile = NULL;
static char word[100];

void initLexer(FILE* file) {
    lexerFile = file;
}

TokenType nextToken() {
    char c = getNextChar();
    
    while(isWhitespace(c)) {
        c = getNextChar();
    }

    switch (c) {
        case '(': 
            return TOKEN_LEFT_PAREN;
        case ')': 
            return TOKEN_RIGHT_PAREN;
        case '{': 
            return TOKEN_LEFT_BRACE;
        case '}': 
            return TOKEN_RIGHT_BRACE;
        case '=': 
            return TOKEN_EQUALS;
        case ';': 
            return TOKEN_SEMICOLON;
        default:
            if (isalpha(c)) {
                return readKeyword(c);
            } else if (isdigit(c)) {
                return readNumber(c);
            }
    }

    return TOKEN_EOF;
}

char getNextChar() {
    return fgetc(lexerFile);
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

TokenType readKeyword(char c) {
    int i = 0;
    word[i++] = c;

    while (isalpha((c = getNextChar())) || isdigit(c) || c == '_') {
        word[i++] = c;
    }

    word[i] = '\0';

    if (!isspace(c) && c != EOF) {
        ungetc(c, lexerFile);
    }

    if(strcmp(word, "void") == 0) {
        return TOKEN_VOID;
    } else if(strcmp(word, "int") == 0) {
        return TOKEN_INT;
    }

    return TOKEN_IDENTIFIER;
}

TokenType readNumber(char c) {
    int i = 0;
    word[i++] = c;

    while (isdigit(c = getNextChar())) {
        word[i++] = c;
    }

    word[i] = '\0';

    if (!isspace(c) && c != EOF) {
        ungetc(c, lexerFile);
    }

    return TOKEN_NUMBER;
}

char* getCurrentTokenValue() {
    return word;
}