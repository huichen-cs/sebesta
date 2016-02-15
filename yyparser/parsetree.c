/**
 * This code is adopted from 
 *    Niemann, Tom. "Lex & yacc tutorial." 
 *    Available: http://epaperpress.com/lexandyacc/
 *    Retrieved on February, 2016
 * where the credit is attributed to Frank Thomas Braun
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsetree.h"

static const int DEL = 1; /* distance of graph columns */
static const int EPS = 3; /* distance of graph lines */

static void graphInit(void);
static void graphFinish(void);
static void exNode(nodeType *p, 
        int c, int l,       /* start colulmn and line of node */
        int *ce, int *cm    /* resulting end column & mid of node */
        );
static void graphDrawBox (char *s, int c, int l);
static void graphBox (char *s, int *w, int *h);
static void graphDrawArrow (int c1, int l1, int c2, int l2);

int ex(nodeType *p) 
{
    int rte, rtm;

    graphInit();
    exNode(p, 0, 0, &rte, &rtm);
    graphFinish();
    
    return 0;
}

/* drawing canvas size: 200 x 200 chracter  */
#define LMAX 200
#define CMAX 200

static char graph[LMAX][CMAX];  /* drawing canvas for ASCII-Graphic */
static int graphNumber = 0;

void graphTest (int l, int c)
{   int ok;
    ok = 1;
    if (l < 0) ok = 0;
    if (l >= LMAX) ok = 0;
    if (c < 0) ok = 0;
    if (c >= CMAX) ok = 0;
    if (ok) return;
    printf ("\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d",
        l, c, LMAX, CMAX);
    exit(1);
}


/* create a blank canvas */
static void graphInit(void)
{
    int i, j;
    for (i = 0; i < LMAX; i ++) {
        for (j = 0; j < CMAX; j ++) {
            graph[i][j] = ' ';
        }
    }
}

static void exNode(nodeType *p, 
        int c, int l,       /* start colulmn and line of node */
        int *ce, int *cm    /* resulting end column & mid of node */
        ) 
{
    int w, h;       /* node width & height */
    char *s;        /* node text */
    int cbar;       /* "real" start column of node (centered above subnodes) */
    int k;          /* child number */
    int che, chm;   /* end column and mid of children */
    int cs;         /* start column of children */
    char word[20];  /* extended node text */

    if (!p) return;

    strcpy(word, "???"); /* should never appear */
    s = word;
    switch(p->type) {
        case typeIntConst: 
            sprintf(word, "%d", p->con.value); 
            break;
        case typeId: 
            strcpy(word, p->id.id); 
            break;
        case typeOpr:
            switch(p->opr.oper) {
                case ';':       s = "[;]";     break;
                case '=':       s = "[=]";     break;
                case '+':       s = "[+]";     break;
                case '-':       s = "[-]";     break;
                case '*':       s = "[*]";     break;
                case '/':       s = "[/]";     break;
                case '<':       s = "[<]";     break;
                case '>':       s = "[>]";     break;
            }
            break;
    }

    /* construct node text box */
    graphBox(s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    /* node is leaf */
    if (p->type == typeIntConst || p->type == typeId || p->opr.nops == 0) {
        graphDrawBox (s, cbar, l);
        return;
    }

    /* node has children */
    cs = c;
    for (k = 0; k < p->opr.nops; k++) {
        exNode (p->opr.op[k], cs, l+h+EPS, &che, &chm);
        cs = che;
    }


    /* total node width */
    if (w < che - c) {
        cbar += (che - c - w) / 2;
        *ce = che;
        *cm = (c + che) / 2;
    }

    /* draw node */
    graphDrawBox (s, cbar, l);

    /* draw arrows (not optimal: children are drawn a second time) */
    cs = c;
    for (k = 0; k < p->opr.nops; k++) {
        exNode (p->opr.op[k], cs, l+h+EPS, &che, &chm);
        graphDrawArrow (*cm, l+h, chm, l+h+EPS-1);
        cs = che;
    }
}

static void graphBox (char *s, int *w, int *h) 
{
    *w = strlen (s) + DEL;
    *h = 1;
}

static void graphDrawBox (char *s, int c, int l) 
{
    int i;
    graphTest (l, c+strlen(s)-1+DEL);
    for (i = 0; i < strlen (s); i++) {
        graph[l][c+i+DEL] = s[i];
    }
}

static void graphDrawArrow (int c1, int l1, int c2, int l2) 
{
    int m;
    graphTest (l1, c1);
    graphTest (l2, c2);
    m = (l1 + l2) / 2;
    while (l1 != m) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    while (c1 != c2) { graph[l1][c1] = '-'; if (c1 < c2) c1++; else c1--; }
    while (l1 != l2) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    graph[l1][c1] = '|';
}

/* print out the graph(s) */
static void graphFinish() {
    int i, j;

    for (i = 0; i < LMAX; i ++) {
        /* skip unused canvas space in row i, null-terminate row i */
        for (j = CMAX - 1; j >= 0 && graph[i][j] == ' '; j --);
        if (j < CMAX - 1) {
            graph[i][j + 1] = 0;
        } else {
           graph[i][CMAX - 1] = 0;   
        }
    }

    /* skip unused rows in canvas */
    for (i = LMAX - 1; i > 0 && graph[i][0] == 0; i --);

    /* print out the graphs */
    printf("\n\nGraph %d:\n", graphNumber ++);
    for (j = 0; j <= i; j ++) {
        printf("\n%s", graph[j]);
    }
    printf("\n");
}


