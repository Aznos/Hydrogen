#include <stdio.h>
#include "../parser/ast.h"

FILE* outputFile;

void generateARMAssembly(FunctionNode* function, const char* outputFileName) {
    outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        printf("Failed to open output file: %s\n", outputFileName);
        return;
    }

    fprintf(outputFile, ".global _main\n");
    fprintf(outputFile, "_main:\n");
    fprintf(outputFile, "    stp x29, x30, [sp, -16]!\n"); // Save the frame pointer and link register
    fprintf(outputFile, "    mov x29, sp\n"); // Set the frame pointer to the current stack pointer

    VariableNode* var = function->variables;
    int stackOffset = 0;
    while (var != NULL) {
        fprintf(outputFile, "    sub sp, sp, #4\n"); // Allocate space for each variable
        fprintf(outputFile, "    mov w0, #%d\n", var->value); // Set the value of the variable
        fprintf(outputFile, "    str w0, [sp, #%d]\n", stackOffset); // Store the value of the variable in the allocated space
        
        stackOffset += 4;
        var = var->next;
    }

    fprintf(outputFile, "    mov w0, 0\n"); // Set the return value to 0 (since no body is implemented)
    fprintf(outputFile, "    ldp x29, x30, [sp], 16\n"); // Restore the frame pointer and link register
    fprintf(outputFile, "    ret\n"); // Return

    fclose(outputFile);
}

void emitPrintString(char* str) {
    fprintf(outputFile, "    ldr r0, =%s\n", str);
    fprintf(outputFile, "    bl printString\n");
}

void emitPrintVariable(char* varName) {
    fprintf(outputFile, "    ldr r0, [%s]\n", varName);
    fprintf(outputFile, "    bl printInt\n");
}