#ifndef PARSER_H
#define PARSER_H

/**
 * three symbol types
 *     integer constants (INT_CONSTANT)
 *     identifier (ID)
 *     operators
 **/
typedef enum {typeIntConst, typeId, typeOpr} nodeEnum;

/* integer constants */
typedef struct {
    int value;
} intConstNodeType;

/* identifiers */
typedef struct {
    char *id;
} idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator     */
    int nops;                   /* number of operants */
    struct nodeTypeTag **op;    /* operants */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;

    union {
        intConstNodeType con;   /* constant */
        idNodeType id;          /* identifier */
        oprNodeType opr;        /* operator */
    };
} nodeType;


nodeType *opr(int oper, int nops, ...);
nodeType *id(char *idname);
nodeType *intConst(int value);

void freeNode(nodeType *p);

#endif
