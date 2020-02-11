CC = gcc
# Enable gdb and pull include files from current dir
CFLAGS = -ggdb -I.
LDFLAGS = 

BINARY = dfs
BUILD_DIR = build

# Capture c files 
c_files = $(wildcard *.c)

# Convert c names to corrosponding o names
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(c_files))

# $@ is the %.o file and $^ is the %.c file
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $^ $(CFLAGS)

# $@ becomes left part thus linked
$(BINARY): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean run

run: $(BINARY)
	./$(BINARY)

hej.png: hej.dot
	dot -Tpng hej.dot > hej.png

hej.dot: $(BINARY)
	./$(BINARY) > hej.dot

draw: hej.png
	nomacs hej.png

clean:
	rm -f $(OBJ) $(BINARY)
	rm hej*
	rmdir $(BUILD_DIR)
