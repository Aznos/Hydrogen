#include "arm_codegen.h"
#include <stdio.h>

void generateARMAssembly(FunctionNode* function, const char* outputFile) {
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Failed to open output file: %s\n", outputFile);
        return;
    }

    fprintf(output, ".global _%s\n", function->functionName);  // Declare function as global
    fprintf(output, "_%s:\n", function->functionName);         // Define function label
    fprintf(output, "    stp x29, x30, [sp, -16]!\n");         // Save frame pointer (x29) and link register (x30)
    fprintf(output, "    mov x29, sp\n");                      // Set up new frame pointer

    // Function body placeholder
    // To be implemented...

    fprintf(output, "    ldp x29, x30, [sp], 16\n");           // Restore frame pointer and link register
    fprintf(output, "    ret\n");                              // Return from the function

    fclose(output);
}