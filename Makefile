CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Isrc/
LDFLAGS := 

SRCDIR := src
BINDIR := bin

SRC := $(shell find $(SRCDIR) -name '*.cpp')
OBJ := $(SRC:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

all: $(BINDIR)/main

$(BINDIR)/main: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BINDIR)/main
	./$(BINDIR)/main

clean:
	rm -rf $(BINDIR)