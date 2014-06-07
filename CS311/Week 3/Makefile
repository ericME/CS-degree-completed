#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #3
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -pedantic-errors
PROGS=homework3


all: $(PROGS)


homework3: homework3.o
	$(CC) $(CFLAGS) -o homework3 homework3.o

homework3.o: homework3.c
	$(CC) $(CFLAGS) -c homework3.c



clean:
	rm -f $(PROGS) *.o *~ *#

