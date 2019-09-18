
HIGHLIGHT_FLAGS= --syntax=c --inline-css

MD_FILES = $(shell find . -type f -name '*.md')
SRC_FILES = $(shell find -name "*.c" -type f)
HDR_FILES = $(shell find -name "*.h" -type f)


HTML_FILES = $(patsubst %.md, %.html, $(MD_FILES))
HTML_FILES += $(patsubst %.c, %-c.html, $(SRC_FILES))
HTML_FILES += $(patsubst %.h, %-h.html, $(HDR_FILES))

index.html: $(HTML_FILES) index.sh
	sh index.sh $(HTML_FILES) | pandoc --output $@

%.html: %.md
	pandoc $^ --output $@

%-c.html: %.c
	highlight $(HIGHLIGHT_FLAGS) --output $@ $^

%-h.html: %.h
	highlight $(HIGHLIGHT_FLAGS) --output $@ $^

.PHONY: all clean

all: $(HTML_FILES) index.html

clean:
	rm -rf $(HTML_FILES)
	rm index.html
