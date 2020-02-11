
LEX=flex
YACC=bison
LIBS=-ly -lfl -lm
CC=gcc

PROG=regn
TRASH=lex.yy.c $(PROG).tab.c $(PROG) $(PROG).tab.h $(PROG).output

$(PROG): $(PROG).tab.o lex.yy.o
		$(CC) -o $@ $^ $(LIBS) 

$(PROG).tab.c $(PROG).tab.h: $(PROG).y
		$(YACC) -d -v $(PROG).y

lex.yy.c: $(PROG).l
		$(LEX) $(PROG).l

%.o: %.c
	$(CC) -c -o $@ $^

PHONY: clean run

run: $(PROG)
	./$(PROG)

clean:
	rm -f *.o
	rm -f $(TRASH)

