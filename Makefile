all: bin/main

bin/main: bin/main.o bin/lexer.o bin/parser.o
	g++ -o bin/main bin/main.o bin/lexer.o bin/parser.o -Wall -Wextra -std=c++17

bin/main.o: src/main.cpp
	mkdir -p bin
	g++ -c src/main.cpp -o bin/main.o -Isrc/ -Wall -Wextra -std=c++17

bin/lexer.o: src/lexer/lexer.cpp
	mkdir -p bin
	g++ -c src/lexer/lexer.cpp -o bin/lexer.o -Isrc/ -Wall -Wextra -std=c++17

bin/parser.o: src/parser/parser.cpp
	mkdir -p bin
	g++ -c src/parser/parser.cpp -o bin/parser.o -Isrc/ -Wall -Wextra -std=c++17

run: bin/main
	./bin/main

clean:
	rm -rf bin