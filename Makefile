all:
	gcc -o main main.c ./src/*.c -I./src -lm

test:
	./main

clean:
	rm -f main

.PHONY: test clean