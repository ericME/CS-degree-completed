#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -pedantic-errors
PROGS=uniquify linkedlist.o
FXNS=linkedlist.o
#functions.o



all: $(PROGS)

uniquify: linkedlist.o uniquify.o functions.h linkedlist.h
	$(CC) $(CFLAGS) -o uniquify uniquify.o $(FXNS)

uniquify.o: uniquify.c functions.h
	$(CC) $(CFLAGS) -c uniquify.c


linkedList.o: linkedList.c linkedList.h
	gcc -g -Wall -std=c99 -c linkedList.c


#EXAMPLE.o: EXAMPLE.c functions.h
#	$(CC) $(CFLAGS) -c EXAMPLE.c



#TESTS


clean:
	rm -f $(PROGS) *.o *~ *#  ~.txt
	rm -fr archive
	rm -fr cmp

