#include "codegen.h"

std::unique_ptr<LLVMContext> context;
std::unique_ptr<Module> module;
std::unique_ptr<IRBuilder<>> builder;
std::map<std::string, Value*> namedValues;

void initModule() {
    context = std::make_unique<LLVMContext>();
    module = std::make_unique<Module>("my cool jit", *context);
    builder = std::make_unique<IRBuilder<>>(*context);
}

Value *logErrorV(const char *str) {
    logError(str);
    return nullptr;
}

Value *NumberExprAST::codegen() {
    return ConstantFP::get(*context, APFloat(val));
}

Value *VariableExprAST::codegen() {
    Value *value = namedValues[name];
    if(!value) {
        return logErrorV("Unknown variable name!");
    }

    return value;
}

Value *BinaryExprAST::codegen() {
    Value *left = LHS->codegen();
    Value *right = RHS->codegen();
    if(!left || !right) {
        return nullptr;
    }

    switch(op) {
        case '+':
            return builder->CreateFAdd(left, right, "addtmp");
        case '-':
            return builder->CreateFSub(left, right, "subtmp");
        case '*':
            return builder->CreateFMul(left, right, "multmp");
        case '<':
            left = builder->CreateFCmpULT(left, right, "cmptmp");
            return builder->CreateUIToFP(left, Type::getDoubleTy(*context), "booltmp");
        default:
            return logErrorV("Invalid binary operator!");
    }
}

Value *CallExprAST::codegen() {
    Function *calleeFn = module->getFunction(callee);
    if(!calleeFn) {
        return logErrorV("Unknown function referenced");
    }

    if(calleeFn->arg_size() != args.size()) {
        return logErrorV("Incorrect number of arguments passed!");
    }
        
    std::vector<Value*> argsValue;
    for(unsigned i = 0, e = args.size(); i != e; i++) {
        argsValue.push_back(args[i]->codegen());
        if(!argsValue.back()) {
            return nullptr;
        }
    }

    return builder->CreateCall(calleeFn, argsValue, "calltmp");
}

Function *PrototypeAST::codegen() {
    std::vector<Type*> Doubles(args.size(), Type::getDoubleTy(*context));
    FunctionType *functionType = FunctionType::get(Type::getDoubleTy(*context), Doubles, false);
    Function *function = Function::Create(functionType, Function::ExternalLinkage, name, module.get());

    unsigned i = 0;
    for(auto &arg : function->args()) {
        arg.setName(args[i++]);
    }

    return function;
}

Function *FunctionAST::codegen() {
    Function* function = module->getFunction(prototype->getName());
    if(!function) {
        function = prototype->codegen();
    }

    if(!function) {
        return nullptr;
    }

    BasicBlock *basicBlock = BasicBlock::Create(*context, "entry", function);
    builder->SetInsertPoint(basicBlock);

    namedValues.clear();
    for(auto &arg : function->args()) {
        namedValues[std::string(arg.getName())] = &arg;
    }

    if(Value *returnValue = body->codegen()) {
        builder->CreateRet(returnValue);
        verifyFunction(*function);
        return function;
    }

    function->eraseFromParent();
    return nullptr;
}