#include "parser.h"
#include <iostream>

std::unique_ptr<FunctionNode> parseFunction() {
    auto node = std::make_unique<FunctionNode>();
    TokenType token;

    token = nextToken();
    if (token != TokenType::VOID) {
        std::cerr << "ERR: Expected \"void\" in function declaration\n";
        return nullptr;
    }
    node->type = "void";

    token = nextToken();
    if (token != TokenType::IDENTIFIER || getCurrentTokenValue() != "main") {
        std::cerr << "ERR: Expected \"main\" in function declaration\n";
        return nullptr;
    }
    node->functionName = "main";

    token = nextToken();
    if (token != TokenType::LEFT_PAREN) {
        std::cerr << "ERR: Expected \"(\"\n";
        return nullptr;
    }

    token = nextToken();
    if (token != TokenType::RIGHT_PAREN) {
        std::cerr << "ERR: Expected \")\"\n";
        return nullptr;
    }

    token = nextToken();
    if (token != TokenType::LEFT_BRACE) {
        std::cerr << "ERR: Expected \"{\" in function declaration\n";
        return nullptr;
    }

    parseFunctionBody(*node);

    token = nextToken();
    if (token != TokenType::RIGHT_BRACE) {
        std::cerr << "ERR: Expected \"}\" in function declaration\n";
        return nullptr;
    }

    return node;
}

void parseFunctionBody(FunctionNode& function) {
    TokenType token;
    while ((token = nextToken()) != TokenType::RIGHT_BRACE) {
        if (token == TokenType::INT) {
            auto var = parseVariableDeclaration();
            if (var) {
                function.variables.push_back(std::move(var));
            }
        } else {
            std::cerr << "ERR: Unexpected token in function body\n";
            break;
        }
    }

    ungetc('}', lexerFile);
}

std::unique_ptr<VariableNode> parseVariableDeclaration() {
    auto node = std::make_unique<VariableNode>();
    node->type = "int";

    TokenType token = nextToken();
    if (token != TokenType::IDENTIFIER) {
        std::cerr << "ERR: Expected identifier in variable declaration\n";
        return nullptr;
    }
    node->name = getCurrentTokenValue();

    token = nextToken();
    if (token != TokenType::EQUALS) {
        std::cerr << "ERR: Expected \"=\" in variable declaration\n";
        return nullptr;
    }

    token = nextToken();
    if (token != TokenType::NUMBER) {
        std::cerr << "ERR: Expected number in variable declaration\n";
        return nullptr;
    }
    node->value = std::stoi(getCurrentTokenValue());

    token = nextToken();
    if (token != TokenType::SEMICOLON) {
        std::cerr << "ERR: Expected \";\" at the end of variable declaration\n";
        return nullptr;
    }

    return node;
}