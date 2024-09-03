#include "codegen.h"

Value *logErrorV(const char *str) {
    logError(str);
    return nullptr;
}

Value *NumberExprAST::codegen() {
    return ConstantFP::get(*context, APFloat(val));
}