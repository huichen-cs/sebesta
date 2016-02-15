all: yyparser

yyparser: y.tab.o lex.yy.o parseerr.o  parser.o  parsetree.o
	$(CC) -g y.tab.o lex.yy.o parseerr.o  parser.o  parsetree.o -o yyparser

.c.o:
	$(CC) -Wall -g -c $<

y.tab.h: sebesta.y
	yacc -d sebesta.y

y.tab.c: sebesta.y
	yacc -d sebesta.y

lex.yy.c: sebesta.l
	lex sebesta.l
		
clean:
	$(RM) y.tab.h y.tab.c *.o lex.yy.c
