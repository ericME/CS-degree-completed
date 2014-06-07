all: prog

prog: linkedListStack.o main.o
	gcc -g -Wall -std=c99 -o prog linkedListStack.o main.o
	
main.o: main.c linkedListStack.h
	gcc -g -Wall -std=c99 -c main.c
	
linkedListStack.o: linkedListStack.c linkedListStack.h
	gcc -g -Wall -std=c99 -c linkedListStack.c

clean:	
	rm linkedListStack.o
	rm main.o
	rm prog
