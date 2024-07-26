LLVM_PREFIX = /opt/homebrew/opt/llvm
CXX = clang++
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I$(LLVM_PREFIX)/include
LDFLAGS = -L$(LLVM_PREFIX)/lib -lLLVM
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
TARGET = $(BIN_DIR)/hydrogen
ARGS = ./src/hydrogen/test.hydro

SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET) $(ARGS)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean run