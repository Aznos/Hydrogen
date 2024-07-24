#include "lexer.h"

void initLexer(char* filePath) {
    
}

TokenType nextToken() {
    char c = getNextChar();
    if(isWhitespace(c)) {
        while(isWhitespace(c)) {
            c = getNextChar();
        }
    } else if(isAlpha(c)) {
        char *word = readKeyword(c);
        if(strcmp(word, "void") == 0) {
            return TOKEN_VOID;
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
    }

    return TOKEN_EOF;
}

char getNextChar() {
    
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

char* readKeyword(char c) {
    char word[100];
    int i = 0;
    word[i++] = c;

    while(isAlpha(c = getNextChar())) {
        word[i++] = c;
    }

    word[i] = '\0';
    return word;
}