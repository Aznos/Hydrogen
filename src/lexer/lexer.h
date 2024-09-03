#ifndef LEXER_H
#define LEXER_H

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

enum Token {
    tok_eof = 1,

    //Keywords
    tok_fn = 2,
    tok_extern = 3,

    //Identifiers
    tok_identifier = 4,
    tok_number = 5,
};

static std::string IdentifierStr; //tok_identifier
static double NumVal; //tok_number

static int getTok();

#endif