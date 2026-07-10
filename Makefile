CC=clang
CFLAGS=-Wall -lraylib

INCLUDES_DIR=include/
SRC_DIR=src
OBJ_DIR=obj

SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET=main

.PHONY: all run clean

all: $(TARGET) run clean

# Links
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run:
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TARGET)
