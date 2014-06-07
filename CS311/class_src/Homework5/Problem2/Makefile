#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -pedantic-errors
PROGS=pipeline
FXNS=
#quick_add.o extract.o toc.o vtoc.o delete.o append.o add_mods.o helpers.o


all: $(PROGS)

pipeline: pipeline.o $(FXNS) functions.h
	$(CC) $(CFLAGS) -o pipeline pipeline.o $(FXNS)

pipeline.o: pipeline.c functions.h
	$(CC) $(CFLAGS) -c pipeline.c

#EXAMPLE.o: EXAMPLE.c functions.h
#	$(CC) $(CFLAGS) -c EXAMPLE.c



#TESTS
test:
	rm -f outfile1 outfile2 myfile1 myfile2
	./pipeline.bash -f outfile2 < simple2.txt > outfile1
	./pipeline -f myfile2 < simple2.txt > myfile1
	sleep 10
	diff outfile1 myfile1
	diff outfile2 myfile2
	rm -f outfile1 outfile2 myfile1 myfile2
	./pipeline.bash -f outfile2 < simple1.txt > outfile1
	./pipeline -f myfile2 < simple1.txt > myfile1
	sleep 10
	diff outfile1 myfile1
	diff outfile2 myfile2
	rm -f outfile1 outfile2 myfile1 myfile2
	./pipeline.bash -f outfile2 < words.txt > outfile1
	./pipeline -f myfile2 < words.txt > myfile1
	sleep 10
	diff outfile1 myfile1
	diff outfile2 myfile2
clean:
	rm -f $(PROGS) *.o *~ outfile1* myfile*

