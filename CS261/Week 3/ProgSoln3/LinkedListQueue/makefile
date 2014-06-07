all: prog

prog: linkedListQueue.o main.o
	gcc -g -Wall -std=c99 -o prog linkedListQueue.o main.o
	
main.o: main.c linkedListQueue.h
	gcc -g -Wall -std=c99 -c main.c
	
linkedListQueue.o: linkedListQueue.c linkedListQueue.h
	gcc -g -Wall -std=c99 -c linkedListQueue.c

clean:	
	rm linkedListQueue.o
	rm main.o
	rm prog
