#ifndef PARSER_H
#define PARSER_H

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

extern int currentTok;
extern int getNextToken() {return currentTok = gettok();}

#endif