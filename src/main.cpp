#include "main.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 30;
    BinopPrecedence['*'] = 40;

    fprintf(stderr, "ready> "); //TODO: implement file reading
    getNextToken();

    mainLoop();

    return 0;
}