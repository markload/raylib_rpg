CC=clang
CFLAGS=-Wall -lraylib
INCLUDES=-I include/
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TARGET=main

all: $(TARGET) run

# Links
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	@rm -rf $(OBJ)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all run clean
