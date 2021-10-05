CC = g++

build: validator
	mkdir -p "bin"
	$(CC) src/main.cpp build/validator.o -o bin/main

validator:
	mkdir -p "build"
	$(CC) src/validator.cpp -c -o build/validator.o

clean:
	rm "bin/main" "build/validator.o"
	rm -d "build" "bin"