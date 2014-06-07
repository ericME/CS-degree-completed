all: prog

prog: dynamicArrayDeque.o main.o
	gcc -g -Wall -std=c99 -o prog dynamicArrayDeque.o main.o
	
main.o: main.c dynamicArrayDeque.h
	gcc -g -Wall -std=c99 -c main.c
	
dynamicArrayDeque.o: dynamicArrayDeque.c dynamicArrayDeque.h
	gcc -g -Wall -std=c99 -c dynamicArrayDeque.c

clean:	
	rm dynamicArrayDeque.o
	rm main.o
	rm prog
