LLVM_PREFIX = /opt/homebrew/opt/llvm
CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra -g -std=c17
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I$(LLVM_PREFIX)/include
LDFLAGS = -L$(LLVM_PREFIX)/lib -lLLVM
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
TARGET = $(BIN_DIR)/hydrogen
ARGS = ./src/hydrogen/test.hydro

SRC_FILES_C = $(shell find $(SRC_DIR) -name '*.c')
SRC_FILES_CPP = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES_C = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES_C))
OBJ_FILES_CPP = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES_CPP))

all: $(TARGET)

$(TARGET): $(OBJ_FILES_C) $(OBJ_FILES_CPP)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES_C) $(OBJ_FILES_CPP) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET) $(ARGS)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean run