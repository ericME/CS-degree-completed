#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #6
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -std=gnu99 -Wall #-Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -pedantic-errors
PROGS=primePThread primeMProc



all: $(PROGS)

primePThread: primePThread.o
	$(CC) $(CFLAGS) -lm -lpthread -lrt -o primePThread primePThread.o
primePThread.o: primePThread.c
	$(CC) $(CFLAGS) -c primePThread.c

primeMProc: primeMProc.o
	$(CC) $(CFLAGS) -lm -lrt -o primeMProc primeMProc.o
primeMProc.o: primeMProc.c
	$(CC) $(CFLAGS) -c primeMProc.c

#EXAMPLE.o: EXAMPLE.c functions.h
#	$(CC) $(CFLAGS) -c EXAMPLE.c



#TESTS
test:
	rm -f outfile1 myfile1
	./primePThread.bash -f < websters.txt > outfile1
	./primePThread -n 5 < websters.txt > myfile1
	diff outfile1 myfile1

clean:
	rm -f $(PROGS) *.o *~ *.primegen *.pthread *.mproc *.eric

