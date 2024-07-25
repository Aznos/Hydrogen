#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "codegen/codegen.h"

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <filename> [--keepasm]\n", argv[0]);
        return 1;
    }

    char llvmFile[] = "output.ll";
    char executableFile[] = "main";
    int keepIR = 0;

    if (argc == 3) {
        if (strcmp(argv[2], "--keepir") == 0) {
            keepIR = 1;
        } else {
            printf("Unknown option: %s\n", argv[2]);
            return 1;
        }
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File not found: %s\n", argv[1]);
        return 1;
    }

    initLexer(file);
    FunctionNode* function = parseFunction();
    if (function) {
        generateLLVMIR(function, llvmFile);

        char compileCmd[512];
        snprintf(compileCmd, sizeof(compileCmd), "clang -o %s %s", executableFile, llvmFile);
        int compileStatus = system(compileCmd);
        if (compileStatus != 0) {
            printf("Compilation failed with status: %d\n", WEXITSTATUS(compileStatus));
            fclose(file);
            return 1;
        }

        if (!keepIR) {
            remove(llvmFile);
        }
    } else {
        printf("Parsing failed\n");
    }

    fclose(file);
    return 0;
}