%{
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "ast.h"
#include "parser.hpp"

%}

%option noyywrap

num [0-9]+
id [a-zA-Z][a-zA-Z0-9_]*

%%

"print" { return PRINT; }
{id}    { yylval.str = new std::string(yytext); return ID; }
{num}   { yylval.i_val = std::atoi(yytext); return NUMBER; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MUL; }
"("     { return OPAR; }
")"     { return CPAR; }
"="     { return EQ; }
";"     { return SEMICOLON; }

[ \t\n\r] /* nothing */

.       {
            throw std::runtime_error(
                std::string("unexpected character:") + yytext);
        }

