#ifndef ARM_CODEGEN_H
#define ARM_CODEGEN_H

#include <stdio.h>
#include "../parser/ast.h"

void generateLLVMIR(FunctionNode* function, const char* outputFile);

#endif