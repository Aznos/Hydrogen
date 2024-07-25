#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>

enum class TokenType {
    VOID,
    INT,
    IDENTIFIER,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    EQUALS,
    NUMBER,
    SEMICOLON,
    EOF_TOKEN
};

class Lexer {
public:
    void initLexer(const std::string& filename);
    TokenType nextToken();
    TokenType readKeyword(char c);
    TokenType readNumber(char c);
    char getNextChar();
    std::string getCurrentTokenValue();
    bool isWhitespace(char c);

private:
    std::ifstream lexerFile;
    std::string currentTokenValue;
};

#endif