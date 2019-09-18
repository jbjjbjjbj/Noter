
MD_FILES = $(wildcard *.md) $(wildcard */*.md)
HTML_FILES = $(patsubst %.md, %.html, $(MD_FILES))


%.html: %.md
	pandoc $^ --output $@

.PHONY: all clean

all: $(HTML_FILES)

clean:
	rm -rf $(HTML_FILES)
