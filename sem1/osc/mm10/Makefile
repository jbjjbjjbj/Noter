opgaver=opg1 opg3

LEX=flex
CC=gcc
LINKFLAG=-lfl
DEFAULT_TARGET=all

%: %.yy.c
	$(CC) -o $@ $^ $(LINKFLAG)

%.yy.c: %.l
	$(LEX) -o $@ $^

all: $(opgaver)

phony: all clean

clean:
	rm $(opgaver)
