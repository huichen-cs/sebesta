all: lexer test

lexer: lexer.c
	$(CC) -Wall lexer.c -o lexer	

test: lexer front.in
	./lexer
