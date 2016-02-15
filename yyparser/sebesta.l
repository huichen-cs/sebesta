/* definition block must be bracketed with %{ and %} markers. */
%{ 
#include <stdio.h>
#include <stdlib.h>
#include "parseerr.h"   /* error handling */
#include "parser.h"
#include "y.tab.h"


int line_no = 1;

%}

%option noinput nounput

/* rule block must be bracked with %% and %% markers. */
%%
[0-9]+ { 
        yylval.iValue = atoi(yytext);   /* yylval is from %union in .y */
        return INT_CONSTANT; 
    }

[A-Za-z][A-Za-z0-9]* { 
        yylval.identifier = malloc(strlen(yytext) + 1);
        if (yylval.identifier == NULL) {
            yyerror("out of memory");
            exit(1);
        }
        strcpy(yylval.identifier, yytext);
        return ID; 
    }

[-+*/()] { return *yytext; }

[ \t\n]+ ; 

.   { yyerror("unknown character"); }
%%

int yywrap(void) {
    return 1;
}


