%{
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "parser.hpp"

%}

%option noyywrap

num [0-9]+
id [a-zA-Z][a-zA-Z0-9_]+

%%

{id}    { yylval.str = new std::string(yytext); return ID; }
\+      { return PLUS; }
\-      { return MINUS; }
\*      { return MUL; }
{num}   { yylval.i_val = std::atoi(yytext); return NUMBER; }

[ \t\n\r] /* nothing */

.       {
            throw std::runtime_error(
                std::string("unexpected character:") + yytext);
        }

