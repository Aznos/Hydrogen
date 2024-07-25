LLVM_PREFIX = /opt/homebrew/opt/llvm
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(LLVM_PREFIX)/include
LDFLAGS = -L$(LLVM_PREFIX)/lib -lLLVM
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
TARGET = $(BIN_DIR)/hydrogen
ARGS = ./src/hydrogen/test.hydro

SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET) $(ARGS)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean run