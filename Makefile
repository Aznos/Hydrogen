all:
	mkdir bin
	g++ ./src/main.cpp -o ./bin/main -Isrc/ -Wall -Wextra

run $(all):
	./bin/main

clean:
	rm -rf ./bin