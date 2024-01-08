all:
	gcc -o main main.c ./src/*.c -I./src -lm

test:
	./main ./input/input.wav ./output/output.wav

clean:
	rm -f main

.PHONY: test clean
