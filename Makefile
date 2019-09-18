
MD_FILES = $(shell find . -type f -name '*.md')
HTML_FILES = $(patsubst %.md, %.html, $(MD_FILES))

index.html: $(HTML_FILES) index.sh
	sh index.sh $(HTML_FILES) | pandoc --output $@

%.html: %.md
	pandoc $^ --output $@


.PHONY: all clean

all: $(HTML_FILES) index.html

clean:
	rm -rf $(HTML_FILES)
	rm index.html
