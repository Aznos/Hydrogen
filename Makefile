CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
TARGET = $(BIN_DIR)/hydrogen

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean