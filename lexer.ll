%{
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "ast/ast.h"
#include "parser.hpp"

%}

%option noyywrap

num [0-9]+
id [a-zA-Z][a-zA-Z0-9_]*

%%

"in"    { return IN; }
"let"   { return LET; }
"where" { return WHERE; }
"print" { return PRINT; }
{id}    { yylval.str = new std::string(yytext); return ID; }
{num}   { yylval.i_val = std::atoi(yytext); return NUMBER; }
"{"     { return OBRACK; }
"}"     { return CBRACK; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MUL; }
"("     { return OPAR; }
")"     { return CPAR; }
"="     { return EQ; }
";"     { return SEMICOLON; }
","     { return COMA; }

[ \t\n\r] /* nothing */

.       {
            throw std::runtime_error(
                std::string("unexpected character:") + yytext);
        }

