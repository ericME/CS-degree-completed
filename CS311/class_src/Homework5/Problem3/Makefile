#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -lm -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -pedantic-errors
PROGS=uniquify
FXNS=linkedlist.o helpers.o
#functions.o



all: $(PROGS)

uniquify: uniquify.o $(FXNS) functions.h linkedlist.h
	$(CC) $(CFLAGS) -o uniquify uniquify.o $(FXNS)
uniquify
.o: uniquify.c functions.h
	$(CC) $(CFLAGS) -c uniquify.c


linkedList.o: linkedList.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedList.c

helpers.o: helpers.c functions.h
	$(CC) $(CFLAGS) -c helpers.c

#EXAMPLE.o: EXAMPLE.c functions.h
#	$(CC) $(CFLAGS) -c EXAMPLE.c



#TESTS
test:
	rm -f outfile1 myfile1
	./uniquify.bash -f < websters.txt > outfile1
	./uniquify -n 5 < websters.txt > myfile1
	diff outfile1 myfile1

clean:
	rm -f $(PROGS) *.o *~ myfile1 outfile1

