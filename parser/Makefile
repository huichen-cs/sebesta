all: parser

parser: front.o parser.o
	$(CC) -Wall front.o parser.o -o parser	

.c.o:
	$(CC) -Wall -c $<


test: parser front.in
	./parser

clean:
	$(RM) parser.o front.o parser
