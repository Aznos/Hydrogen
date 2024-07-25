#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cstdio>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "codegen/codegen.h"

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> [--keepir]\n";
        return 1;
    }

    std::string llvmFile = "output.ll";
    std::string executableFile = "main";
    bool keepIR = false;

    if (argc == 3) {
        if (std::string(argv[2]) == "--keepir") {
            keepIR = true;
        } else {
            std::cerr << "Unknown option: " << argv[2] << "\n";
            return 1;
        }
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "File not found: " << argv[1] << "\n";
        return 1;
    }

    initLexer(file);
    std::unique_ptr<FunctionNode> function(parseFunction());
    if (function) {
        generateLLVMIR(function.get(), llvmFile.c_str());

        std::string compileCmd = "clang -o " + executableFile + " " + llvmFile;
        int compileStatus = system(compileCmd.c_str());
        if (compileStatus != 0) {
            std::cerr << "Compilation failed with status: " << WEXITSTATUS(compileStatus) << "\n";
            return 1;
        }

        if (!keepIR) {
            std::remove(llvmFile.c_str());
        }
    } else {
        std::cerr << "Parsing failed\n";
        return 1;
    }

    return 0;
}