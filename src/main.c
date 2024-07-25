#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "codegen/arm_codegen.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char assemblyFile[] = "temp.s";
    char objectFile[] = "temp.o";
    char executableFile[] = "main";

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File not found: %s\n", argv[1]);
        return 1;
    }

    initLexer(file);
    FunctionNode* function = parseFunction();
    if (function) {
        generateARMAssembly(function, assemblyFile);

        char assembleCmd[512];
        snprintf(assembleCmd, sizeof(assembleCmd), "as -o %s %s", objectFile, assemblyFile);
        system(assembleCmd);

        char linkCmd[512];
        snprintf(linkCmd, sizeof(linkCmd), "gcc -o %s %s", executableFile, objectFile);
        system(linkCmd);

        remove(assemblyFile);
        remove(objectFile);
    } else {
        printf("Parsing failed\n");
    }

    fclose(file);
    return 0;
}