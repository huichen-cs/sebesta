#include <stdarg.h>
#include <stdlib.h>
#include "parseerr.h"
#include "parser.h"

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    p = malloc(sizeof(nodeType));
    if (p == NULL) {
        yyerror("out of memory");
    }
    p->opr.op = malloc(nops * sizeof(nodeType*));
    if (p->opr.op == NULL) {
        yyerror("out of memory");
    }

    p->type = typeOpr;  /* operator node type */
    p->opr.oper = oper; /* operator */
    p->opr.nops = nops; /* number of operants */
    va_start(ap, nops);
    for (i = 0; i < nops; i ++) {
        p->opr.op[i] = va_arg(ap, nodeType*);
    }
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) 
{
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i ++) {
            freeNode(p->opr.op[i]);
        }
        free(p->opr.op);
    } else if (p->type == typeId) {
        free(p->id.id);
    }
    free (p);
}


nodeType *id(char *idname) 
{
    nodeType *p;

    p = malloc(sizeof(nodeType));
    if (p == NULL) {
        yyerror("out of memory");
    }

    p->type = typeId;
    p->id.id = idname;

    return p;
}

nodeType *intConst(int value)
{
    nodeType *p;

    p = malloc(sizeof(nodeType));
    if (p == NULL) {
        yyerror("out of memory");
    }

    p->type = typeIntConst;
    p->con.value = value;

    return p;
}
