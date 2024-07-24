#include "arm_codegen.h"

void generateARMAssembly(FunctionNode* function, const char* outputFile) {
    FILE* output = fopen(outputFile, "w");
    if(!output) {
        printf("Failed to open output file: %s\n", outputFile);
        return;
    }

    fprintf(output, ".global _%s\n", function->functionName);
    fprintf(output, "_%s:\n", function->functionName); //Define function label
    fprintf(output, "   push {lr}\n"); //Put link register on stack
    fprintf(output, "   sub sp, sp, #4\n"); //Make space for local variables

    //Add body when I implement

    fprintf(output, "   add sp, sp, #4\n"); //Restore stack pointer
    fprintf(output, "   pop {pc}\n"); //Restore link register

    fclose(output);
}