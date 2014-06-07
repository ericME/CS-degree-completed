all: prog

prog: linkedList.o main.o
	gcc -g -Wall -std=c99 -o prog linkedList.o main.o
	
main.o: main.c linkedList.h
	gcc -g -Wall -std=c99 -c main.c
	
linkedList.o: linkedList.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedList.c

clean:	
	rm linkedList.o
	rm main.o
	rm prog
