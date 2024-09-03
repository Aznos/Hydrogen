#ifndef LEXER_H
#define LEXER_H

#include "main.h"

enum Token {
    tok_eof = 1,

    //Keywords
    tok_fn = 2,
    tok_extern = 3,

    //Identifiers
    tok_identifier = 4,
    tok_number = 5 //For now we're just having doubles so no type defs needed
};

static std::string IdentifierStr; //tok_identifier
static double NumVal; //tok_number

int getTok();

#endif