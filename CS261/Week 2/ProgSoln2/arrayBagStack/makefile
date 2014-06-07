all: prog

prog: arrayBagStack.o main.o
	gcc -g -Wall -std=c99 -o prog arrayBagStack.o main.o
	
main.o: main.c arrayBagStack.h
	gcc -g -Wall -std=c99 -c main.c
	
arrayBagStack.o: arrayBagStack.c arrayBagStack.h
	gcc -g -Wall -std=c99 -c arrayBagStack.c

clean:	
	rm arrayBagStack.o
	rm main.o
	rm prog
