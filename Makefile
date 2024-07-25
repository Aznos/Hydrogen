# Specify the LLVM installation prefix obtained from `brew --prefix llvm`
LLVM_PREFIX = /opt/homebrew/opt/llvm

# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I$(LLVM_PREFIX)/include
LDFLAGS = -L$(LLVM_PREFIX)/lib -lLLVM

# Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj
TARGET = $(BIN_DIR)/hydrogen
ARGS = ./src/hydrogen/test.hydro

# Source and object files
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled program
run: $(TARGET)
	$(TARGET) $(ARGS)

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean run