%{

#include <stdexcept>

#include "ast.h"

int yylex();
void yyerror(const char* error);

Block* g_res;

%}

%union{
    int i_val;
    std::string* str;
    Expr* expr;
    Instr* instr;
    Block* block;
}

%token <str> ID
%token <i_val> NUMBER
%token PLUS "+"
%token MINUS "-"
%token MUL "*"
%token OPAR "("
%token CPAR ")"
%token EQ "="
%token SEMICOLON ";"
%token PRINT "print"

%type <expr> Term
%type <expr> Factors
%type <expr> Adds
%type <expr> Expr
%type <instr> Affectation
%type <instr> Instr
%type <block> Blocks

%start All

%%

All:
   Blocks               { g_res = $1; }
   ;

Blocks:
    Blocks Instr        { $1->Append($2); $$ = $1; }
    | /* empty */       { $$ = new Block; }
    ;

Instr:
     Affectation ";"    { $$ = $1; }
     | Expr ";"         { $$ = $1; }
     | "print" Expr ";" { $$ = new Print($2);; }
     ;

Affectation:
    ID "=" Expr         { $$ = new VarSet(*$1, $3); delete $1; }
    ;

Expr:
    Adds                { $$ = $1; }
    ;

Adds:
    Adds "+" Factors    { $$ = new Add($1, $3); }
    | Adds "-" Factors  { $$ = new Sub($1, $3); }
    | Factors           { $$ = $1; }
    ;

Factors:
    Factors "*" Term    { $$ = new Mul($1, $3); }
    | Term              { $$ = $1; }
    ;

Term:
    ID                  { $$ = new VarGet(*$1); delete $1; }
    | NUMBER            { $$ = new IntLit($1); }
    | "(" Expr ")"      { $$ = $2; }
    ;

%%

void yyerror(const char* error) {
    throw std::runtime_error(error);
}

int main() {
    yyparse();
    Context ctx;
    g_res->Eval(ctx);
    return 0;
}
