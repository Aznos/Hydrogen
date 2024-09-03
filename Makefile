all:
	mkdir bin
	g++ ./src/main.cpp -o ./bin/main

run $(all):
	./bin/main

clean:
	rm -rf ./bin