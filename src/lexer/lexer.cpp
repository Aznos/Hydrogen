#include "lexer.h"

int getTok() { //Return next token
    int lastChar = ' ';

    while(isspace(lastChar))
        lastChar = getchar();

    if(isalpha(lastChar)) {
        IdentifierStr = lastChar;
        while(isalnum((lastChar = getchar())))
            IdentifierStr += lastChar;

        if(IdentifierStr == "fn")
            return tok_fn;
        if(IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }

    if(isdigit(lastChar) || lastChar == '.') {
        std::string numStr;
        do {
            numStr += lastChar;
            lastChar = getchar();
        } while(isdigit(lastChar) || lastChar == '.');

        NumVal = strtod(numStr.c_str(), nullptr);
        return tok_number;
    }

    if (lastChar == '/' && (lastChar = getchar()) == '/') {
        do
            lastChar = getchar();
        while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF) {
            return getTok();
        }
    }

    if(lastChar == EOF)
        return tok_eof;

    int thisChar = lastChar;
    lastChar = getchar();
    return thisChar;
}