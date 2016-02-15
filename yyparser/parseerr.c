#include <stdio.h>
#include "parseerr.h"

void yyerror(char *s) 
{
    fprintf(stdout, "%s\n", s);
}
