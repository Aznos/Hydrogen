#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "codegen/arm_codegen.h"

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <filename> [--keepasm]\n", argv[0]);
        return 1;
    }

    char assemblyFile[] = "temp.s";
    char objectFile[] = "temp.o";
    char executableFile[] = "main";
    char printUtilsObjectFile[] = "print_utils.o";
    int keepAsm = 0;

    if (argc == 3) {
        if (strcmp(argv[2], "--keepasm") == 0) {
            keepAsm = 1;
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
        generateARMAssembly(function, assemblyFile);

        char assembleCmd[512];
        snprintf(assembleCmd, sizeof(assembleCmd), "as -g -o %s %s", objectFile, assemblyFile);
        int assembleStatus = system(assembleCmd);
        if (assembleStatus != 0) {
            printf("Assembly failed with status: %d\n", WEXITSTATUS(assembleStatus));
            fclose(file);
            return 1;
        }

        snprintf(assembleCmd, sizeof(assembleCmd), "as -g -o %s src/codegen/print_utils.s", printUtilsObjectFile);
        assembleStatus = system(assembleCmd);
        if (assembleStatus != 0) {
            printf("Assembly of print_utils.s failed with status: %d\n", WEXITSTATUS(assembleStatus));
            fclose(file);
            return 1;
        }

        char linkCmd[512];
        snprintf(linkCmd, sizeof(linkCmd), "gcc -g -o %s %s %s -lc", executableFile, objectFile, printUtilsObjectFile);
        int linkStatus = system(linkCmd);
        if (linkStatus != 0) {
            printf("Linking failed with status: %d\n", WEXITSTATUS(linkStatus));
            fclose(file);
            return 1;
        }

        if (!keepAsm) {
            remove(assemblyFile);
            remove(objectFile);
            remove(printUtilsObjectFile);
        }
    } else {
        printf("Parsing failed\n");
    }

    fclose(file);
    return 0;
}