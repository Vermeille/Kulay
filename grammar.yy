%{

#include <stdexcept>

#include "ast/ast.h"
#include "ast/interpretervisitor.h"

int yylex();
void yyerror(const char* error);

Block* g_res;

%}

%define parse.error verbose
%debug

%union{
    int i_val;
    std::string* str;
    Expr* expr;
    Instr* instr;
    Block* block;
    Decls* decls;
    VarSet* affectation;
    InstrBody* instr_body;
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
%token COMA ","
%token PRINT "print"
%token OBRACK "{"
%token CBRACK "}"
%token LET "let"
%token IN "in"
%token WHERE "where"

%type <expr> Term
%type <expr> Factors
%type <expr> Adds
%type <expr> Expr
%type <affectation> Affectation
%type <instr_body> InstrBody
%type <instr> Instr
%type <block> Instrs
%type <decls> LetClause
%type <decls> WhereClause
%type <decls> Affectations

%start All

%%

All:
   Instrs               { g_res = $1; }
   ;

Instrs:
    Instrs ";" Instr    { $1->Append($3); $$ = $1; }
    | Instr             { $$ = new Block; $$->Append($1); }
    ;

Instr:
    LetClause InstrBody WhereClause { $$ = new Instr($1, $2, $3); }
    ;

LetClause:
    "let" Affectations "in" { $$ = $2; }
    | /* empty */           { $$ = nullptr; }
    ;

WhereClause:
    "where" Affectations    { $$ = $2; }
    | /* empty */           { $$ = nullptr; }
    ;

InstrBody:
     Affectation        { $$ = $1; }
     | Expr             { $$ = new ExprInstr($1); }
     | "print" Expr     { $$ = new Print($2); }
     | "{" Instrs "}"   { $$ = $2; }
     ;

Affectation:
    ID "=" InstrBody    { $$ = new VarSet(*$1, $3); delete $1; }
    ;

Affectations:
    Affectations "," Affectation    { $1->Append($3); $$ = $1; }
    | Affectation       { $$ = new Decls; $$->Append($1); }
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
    //yydebug = 1;
    yyparse();
    g_res->PrettyPrint();
    InterpreterVisitor v;
    g_res->Accept(v);
    return 0;
}
