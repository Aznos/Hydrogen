#include <stdio.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: ./hydrogen <filename>\n");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("File not found: %s\n", argv[1]);
        return 1;
    }

    initLexer(file);
    FunctionNode* function = parseFunction();
    if(function) {
        printf("Function: %s %s()\n", function->returnType, function->functionName);
        free(function);
    } else {
        printf("Parsing failed\n");
    }

    fclose(file);
}