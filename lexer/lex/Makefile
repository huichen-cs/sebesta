all: lexer


lexer: sebesta.l
	lex sebesta.l
	$(CC) lex.yy.c -o lexer

test: lexer ../front.in
	./lexer < ../front.in

clean: 
	$(RM) lexer  lex.yy.c
