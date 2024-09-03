#include "parser.h"

int getNextToken() {
    return currentTok = getTok();
}

int getTokPrecedence() {
    if(!isascii(currentTok))
        return -1;

    int tokPrec = BinopPrecedence[currentTok];
    if(tokPrec <= 0)
        return -1;
    
    return tokPrec;
}

std::unique_ptr<ExprAST> logError(const char *str) {
    fprintf(stderr, "Err: %s\n", str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> logErrorP(const char *str) {
    logError(str);
    return nullptr;
}

std::unique_ptr<ExprAST> parseNumberExpr() {
    auto res = std::make_unique<NumberExprAST>(NumVal);
    getNextToken();
    return std::move(res);
}

std::unique_ptr<ExprAST> parseParenExpr() {
    getNextToken(); //(
    auto val = parseExpression();
    if(!val) 
        nullptr;
    
    if(currentTok != ')')
        return logError("Expected ')'");
    
    getNextToken(); //)
    return val;
}

std::unique_ptr<ExprAST> parseIdentifierExpr() {
    std::string idName = IdentifierStr;
    getNextToken(); //Identifier

    if(currentTok != '(')
        return std::make_unique<VariableExprAST>(idName);

    getNextToken(); //(
    std::vector<std::unique_ptr<ExprAST> > args;
    if(currentTok != ')') {
        while(true) {
            if(auto arg = parseExpression())
                args.push_back(std::move(arg));
            else
                return nullptr;

            if(currentTok == ')')
                break;

            if(currentTok != ',')
                return logError("Expected ')' or ',' in argument list");

            getNextToken();
        }
    }

    getNextToken(); //)
    return std::make_unique<CallExprAST>(idName, std::move(args));
}

std::unique_ptr<ExprAST> parsePrimary() {
    switch(currentTok) {
        case tok_identifier:
            return parseIdentifierExpr();
        case tok_number:
            return parseNumberExpr();
        case '(':
            return parseParenExpr();
        default:
            return logError("Unknown token when expecting an expression");
    }
}

std::unique_ptr<ExprAST> parseBinopRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    while(true) {
        int tokPrec = getTokPrecedence();
        if(tokPrec < ExprPrec)
            return LHS;

        int binOp = currentTok;
        getNextToken(); //binop

        auto RHS = parsePrimary();
        if(!RHS)
            return nullptr;
        
        int nextPrec = getTokPrecedence();
        if(tokPrec < nextPrec) {
            RHS = parseBinopRHS(tokPrec + 1, std::move(RHS));
            if(!RHS)
                return nullptr;
        }

        LHS = std::make_unique<BinaryExprAST>(binOp, std::move(LHS), std::move(RHS));
    }
}

std::unique_ptr<ExprAST> parseExpression() {
    auto LHS = parsePrimary();
    if(!LHS)
        return nullptr;

    return parseBinopRHS(0, std::move(LHS));
}

std::unique_ptr<ExprAST> parsePrototype() {
    if(currentTok != tok_identifier)
        return logErrorP("Expected function name in prototype");

    std::string functionName = IdentifierStr;
    getNextToken();

    if(currentTok != '(')
        return LogErrorP("Expected '(' in prototype");

    std::vector<std::string> argNames;
    while(getNextToken() == tok_identifier)
        argNames.push_back(IdentifierStr);
    
    if(currentTok != ')')
        return logErrorP("Expected ')' in prototype");

    getNextToken(); //)
    return std::make_unique<PrototypeAST>(functionName, std::move(argNames));
}

std::unique_ptr<FunctionAST> parseFunction() {
    getNextToken(); //fn
    auto prototype = ParsePrototype();
    if(!prototype)
        return nullptr;

    if(auto expr = parseExpression())
        return std::make_unique<FunctionAST>(std::move(prototype), std::move(expr));

    return nullptr;
}

std::unqiue_ptr<FunctionAST> parseTopLevelExpr() {
    if(auto expr = ParseExpression()) {
        auto prototype = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(prototype), std::move(expr));
    }

    return nullptr;
}

std::unique_ptr<PrototypeAST> parseExtern() {
    getNextToken(); //extern
    return parsePrototype();
}

void handleFunction() {
    if(parseFunction()) {
        fprintf(stderr, "Parsed a function definition\n");
    } else {
        getNextToken(); //Skip token
    }
}

void handleExtern() {
    if(parseExtern()) {
        fprintf(stderr, "Parsed an extern\n");
    } else {
        getNextToken();
    }
}

void handletopLevelExpr() {
    if(parseTopLevelExpr()) {
        fprintf(stderr, "Parsed a top level expression\n");
    } else {
        getNextToken();
    }
}

void mainLoop() {
    while(true) {
        fprintf(stderr, "ready> "); //TODO: implement file reading
        switch(currentTok) {
            case tok_eof:
                return;
            case ';':
                getNextToken();
                break;
            case tok_fn:
                handleFunciton();
                break;
            case tok_extern:
                handleExtern();
                break;
            default:
                handleTopLevelExpr();
                break;
        }
    }
}