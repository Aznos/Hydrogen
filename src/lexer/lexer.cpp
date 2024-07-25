#include "lexer.h"
#include <cctype>

void Lexer::initLexer(const std::string& filename) {
    lexerFile.open(filename);
    if (!lexerFile) {
        throw std::runtime_error("File could not be opened: " + filename);
    }
}

TokenType Lexer::nextToken() {
    char c = getNextChar();

    while (isWhitespace(c)) {
        c = getNextChar();
    }

    switch (c) {
        case '(': 
            return TokenType::LEFT_PAREN;
        case ')': 
            return TokenType::RIGHT_PAREN;
        case '{': 
            return TokenType::LEFT_BRACE;
        case '}': 
            return TokenType::RIGHT_BRACE;
        case '=': 
            return TokenType::EQUALS;
        case ';': 
            return TokenType::SEMICOLON;
        default:
            if (std::isalpha(c)) {
                return readKeyword(c);
            } else if (std::isdigit(c)) {
                return readNumber(c);
            }
    }

    return TokenType::EOF_TOKEN;
}

char Lexer::getNextChar() {
    return lexerFile.get();
}

bool Lexer::isWhitespace(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

TokenType Lexer::readKeyword(char c) {
    currentTokenValue.clear();
    currentTokenValue += c;

    while (std::isalpha((c = getNextChar())) || std::isdigit(c) || c == '_') {
        currentTokenValue += c;
    }

    if (!isWhitespace(c) && c != std::char_traits<char>::eof()) {
        lexerFile.unget();
    }

    if (currentTokenValue == "void") {
        return TokenType::VOID;
    } else if (currentTokenValue == "int") {
        return TokenType::INT;
    }

    return TokenType::IDENTIFIER;
}

TokenType Lexer::readNumber(char c) {
    currentTokenValue.clear();
    currentTokenValue += c;

    while (std::isdigit(c = getNextChar())) {
        currentTokenValue += c;
    }

    if (!isWhitespace(c) && c != std::char_traits<char>::eof()) {
        lexerFile.unget();
    }

    return TokenType::NUMBER;
}

std::string Lexer::getCurrentTokenValue() {
    return currentTokenValue;
}