#ifndef ARM_CODEGEN_H
#define ARM_CODEGEN_H

#include <stdio.h>
#include "../parser/ast.h"

void generateARMAssembly(FunctionNode* function, const char* outputFile);
void emitPrintString(char* str);
void emitPrintVariable(char* varName);

#endif