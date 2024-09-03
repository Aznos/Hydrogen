all:
	mkdir bin
	g++ ./src/main.cpp ./src/lexer/lexer.c ./src/parser/parser.c -o ./bin/main -Isrc/ -Wall -Wextra

run $(all):
	./bin/main

clean:
	rm -rf ./bin