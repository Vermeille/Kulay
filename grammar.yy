%{

#include <string>
#include <stdexcept>
#include <iostream>
#include <map>

int yylex();
void yyerror(const char* error);

std::map<std::string, int> vars;

int g_res;

%}

%union{
    int i_val;
    std::string* str;
}

%token <str> ID
%token <i_val> NUMBER
%token PLUS "+"
%token MINUS "-"
%token MUL "*"

%type <i_val> Term
%type <i_val> Factors
%type <i_val> Adds
%type <i_val> Expr

%start Expr

%left PLUS
%left MUL

%%

Expr:
    Adds                { $$ = $1; g_res = $1; }
    ;

Adds:
    Factors "+" Adds    { $$ = $1 + $3; }
    | Factors "-" Adds    { $$ = $1 - $3; }
    | Factors           { $$ = $1; }
    ;

Factors:
    Term "*" Factors    { $$ = $1 * $3; }
    | Term              { $$ = $1; }
    ;

Term:
    ID          { $$ = vars[*$1]; }
    | NUMBER    { $$ = $1; }
    ;


%%

void yyerror(const char* error) {
    throw std::runtime_error(error);
}

int main() {
    vars["caca"] = 3;
    std::cout << "caca = " << vars["caca"] << std::endl;
    yyparse();
    std::cout << g_res << std::endl;
    return 0;
}
