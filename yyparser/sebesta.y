%{
#include "parser.h"
#include "parseerr.h"
#include "parsetree.h"
int yylex(void);
%}

%union {
    int iValue;
    char *identifier;
    nodeType *nPtr;
};

%token <iValue> INT_CONSTANT
%token <identifier> ID 

%left '+' '-'

%type <nPtr> expr term factor

%%

program:
    expr                { ex($1); freeNode($1); }
    | 
    ;

/* 
 *   <expr> -> <term> {( + | - ) <term>}
 **/
expr:
        expr '+' term       { $$ = opr('+', 2, $1, $3); }
    |   expr '-' term       { $$ = opr('-', 2, $1, $3); }
    |   term                { $$ = $1; }
    ;

/*
 * <term> -> <factor> {( * | / ) <factor>)
 **/
term:
        term '*' factor     { $$ = opr('*', 2, $1, $3); }
    |   term '/' factor     { $$ = opr('/', 2, $1, $3); }
    |   factor              { $$ = $1; }
    ;

/*
 * <factor> -> id | int_constant | ( <expr> )
 **/
factor:
        ID                { $$ = id($1); }
    |   INT_CONSTANT      { $$ = intConst($1); }
    |   '(' expr ')'      { $$ = $2; }
    ;

%%

int main() {
    yyparse();
    return 0;
}

