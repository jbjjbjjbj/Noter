opgaver=opg1 opg3 opg4

LEX=flex
CC=gcc
LINKFLAG=-lfl
DEFAULT_TARGET=all

%: %.yy.c
	$(CC) -o $@ $^ $(LINKFLAG)

%.o: %.c
	$(CC) -c -o $@ $^

%.yy.c: %.l
	$(LEX) -o $@ $^

all: $(opgaver)

phony: all clean run

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(opgaver)
