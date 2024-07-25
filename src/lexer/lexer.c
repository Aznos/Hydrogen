#include "lexer.h"

static FILE* lexerFile = NULL;

void initLexer(FILE* file) {
    lexerFile = file;
}

TokenType nextToken() {
    char c = getNextChar();
    
    while(isWhitespace(c)) {
        c = getNextChar();
    }

    if(isalpha(c)) {
        char *word = readKeyword(c);
        if(strcmp(word, "void") == 0) {
            return TOKEN_VOID;
        } else if(strcmp(word, "int") == 0) {
            return TOKEN_INT;
        } else {
            return TOKEN_IDENTIFIER;
        }
    } else if(c == '(') {
        return TOKEN_LEFT_PAREN;
    } else if(c == ')') {
        return TOKEN_RIGHT_PAREN;
    } else if(c == '{') {
        return TOKEN_LEFT_BRACE;
    } else if(c == '}') {
        return TOKEN_RIGHT_BRACE;
    } else if(c == '=') {
        return TOKEN_EQUALS;
    } else if(isdigit(c)) {
        return TOKEN_NUMBER;
    } else if(c == ';') {
        return TOKEN_SEMICOLON;
    }

    return TOKEN_EOF;
}

char getNextChar() {
    return fgetc(lexerFile);
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

char* readKeyword(char c) {
    static char word[100];
    int i = 0;
    word[i++] = c;

    while(isalpha((c = getNextChar())) || isdigit(c) || c == '_') {
        word[i++] = c;
    }

    word[i] = '\0';

    if(!isspace(c) && c != EOF) {
        ungetc(c, lexerFile);
    }

    return word;
}