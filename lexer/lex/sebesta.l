%option noyywrap

digit   [0-9]
letter  [A-Za-z]

/* definition block must be bracketed with %{ and %} markers. */
%{ 
int line_no = 1;

#define ERROR      -99
#define END_OF_LINE -2
#define END_OF_FILE -1
#define INT_LIT     10
#define IDENT       11
#define ASSIGN_OP   20
#define ADD_OP      21
#define SUB_OP      22
#define MULT_OP     23
#define DIV_OP      24
#define LEFT_PAREN  25
#define RIGHT_PAREN 26
%}
/* rule block must be bracked with %% and %% markers. */
%%
[\t ]+ /* ignore white space */
{letter}({letter}|{digit})* { return IDENT; }
{digit}+ { return INT_LIT; }
\( { return LEFT_PAREN; }
\) { return RIGHT_PAREN; }
\+ { return ADD_OP; }
\- { return SUB_OP; }
\* { return MULT_OP; }
\/ { return DIV_OP; }
\n  { line_no ++; return END_OF_LINE; }
.  { return ERROR; }
<<EOF>> {return END_OF_FILE;}
%%

int main() 
{
    int token;
    while (token = yylex()) {
        switch (token) {
            case IDENT: 
            case INT_LIT:
            case LEFT_PAREN:
            case RIGHT_PAREN:
            case ADD_OP:
            case SUB_OP:
            case MULT_OP:
            case DIV_OP:
            printf("Next token is: %d, Next lexeme is %s\n", token, yytext);
            break;

            case END_OF_FILE:
            printf("Next token is: %d, Next lexeme is %s\n", token, "EOF");
            yyterminate();
            break;

            case ERROR:
            printf("ERROR: unexpected %c",yytext[0]);
            break;
        }
    }
}
