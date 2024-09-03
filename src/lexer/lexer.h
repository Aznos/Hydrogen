#ifndef LEXER_H
#define LEXER_H

enum Token {
    tok_eof = 1,

    //Keywords
    tok_fn = 2,
    tok_extern = 3,

    //Identifiers
    tok_identifier = 4,
    tok_number = 5,
};

#endif