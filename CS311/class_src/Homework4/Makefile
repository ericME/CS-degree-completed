#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -pedantic-errors
PROGS=sig_demo myar
FXNS=quick_add.o extract.o toc.o vtoc.o delete.o append.o add_mods.o helpers.o


all: $(PROGS)


sig_demo: sig_demo.o
	$(CC) $(CFLAGS) -o sig_demo sig_demo.o

sig_demo.o: sig_demo.c
	$(CC) $(CFLAGS) -c sig_demo.c

myar: myar.o $(FXNS) functions.h
	$(CC) $(CFLAGS) -o myar myar.o $(FXNS)

myar.o: myar.c functions.h
	$(CC) $(CFLAGS) -c myar.c

quick_add.o: quick_add.c functions.h
	$(CC) $(CFLAGS) -c quick_add.c

extract.o: extract.c functions.h
	$(CC) $(CFLAGS) -c extract.c

toc.o: toc.c functions.h
	$(CC) $(CFLAGS) -c toc.c

vtoc.o: vtoc.c functions.h
	$(CC) $(CFLAGS) -c vtoc.c

delete.o: delete.c functions.h
	$(CC) $(CFLAGS) -c delete.c

append.o: append.c functions.h
	$(CC) $(CFLAGS) -c append.c

add_mods.o: add_mods.c functions.h
	$(CC) $(CFLAGS) -c add_mods.c

helpers.o: helpers.c functions.h
	$(CC) $(CFLAGS) -c helpers.c

#TESTS
testq12345:
	rm -f ar12345.ar myar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	./myar -q myar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	diff ar12345.ar myar12345.ar

testq135:
	rm -f ar135.ar myar135.ar
	ar q ar135.ar 1-s.txt 3-s.txt 5-s.txt
	./myar -q myar135.ar 1-s.txt 3-s.txt 5-s.txt
	diff ar135.ar myar135.ar

testq24:
	rm -f ar24.ar myar24.ar
	ar q ar24.ar 2-s.txt 4-s.txt
	./myar -q myar24.ar 2-s.txt 4-s.txt
	diff ar24.ar myar24.ar

testq: testq12345 testq135 testq24

testt12345:
	rm -f ar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	ar t ar12345.ar > ar-ctoc.txt
	./myar -t ar12345.ar > myar-ctoc.txt
	diff ar-ctoc.txt myar-ctoc.txt

testt135:
	rm -f ar135.ar
	ar q ar135.ar 1-s.txt 3-s.txt 5-s.txt
	ar t ar135.ar > ar-ctoc.txt
	./myar -t ar135.ar > myar-ctoc.txt
	diff ar-ctoc.txt myar-ctoc.txt
testt24:
	rm -f ar24.ar 
	ar q ar24.ar 2-s.txt 4-s.txt
	ar t ar24.ar > ar-ctoc.txt
	./myar -t ar24.ar > myar-ctoc.txt
	diff ar-ctoc.txt myar-ctoc.txt

testt: testt12345 testt135 testt24

testv12345:
	rm -f ar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	ar tv ar12345.ar > ar-vtoc.txt
	./myar -v ar12345.ar > myar-vtoc.txt
	diff ar-vtoc.txt myar-vtoc.txt

testv135:
	rm -f ar135.ar
	ar q ar135.ar 1-s.txt 3-s.txt 5-s.txt
	ar tv ar135.ar > ar-vtoc.txt
	./myar -v ar135.ar > myar-vtoc.txt
	diff ar-vtoc.txt myar-vtoc.txt
testv24:
	rm -f ar24.ar 
	ar q ar24.ar 2-s.txt 4-s.txt
	ar tv ar24.ar > ar-ctoc.txt
	./myar -v ar24.ar > myar-ctoc.txt
	diff ar-vtoc.txt myar-vtoc.txt

testv: testv12345 testv135 testv24

testcreate:
	rm -f ar12345.ar
	ar q ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt

testx12345: testcreate
	rm -fr cmp
	mkdir cmp
	ar x ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	mv 1-s.txt ./cmp
	mv 2-s.txt ./cmp
	mv 3-s.txt ./cmp
	mv 4-s.txt ./cmp
	mv 5-s.txt ./cmp
	./myar -x ar12345.ar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	diff ./cmp/1-s.txt 1-s.txt
	diff ./cmp/2-s.txt 2-s.txt
	diff ./cmp/3-s.txt 3-s.txt
	diff ./cmp/4-s.txt 4-s.txt
	diff ./cmp/5-s.txt 5-s.txt

testx135: testcreate
	rm -fr cmp
	mkdir cmp
	ar x ar12345.ar 1-s.txt 3-s.txt 5-s.txt
	mv 1-s.txt ./cmp
	mv 3-s.txt ./cmp
	mv 5-s.txt ./cmp
	./myar -x ar12345.ar 1-s.txt 3-s.txt 5-s.txt
	diff ./cmp/1-s.txt 1-s.txt
	diff ./cmp/3-s.txt 3-s.txt
	diff ./cmp/5-s.txt 5-s.txt


testx24: testcreate
	rm -fr cmp
	mkdir cmp
	ar x ar12345.ar 2-s.txt 4-s.txt
	mv 2-s.txt ./cmp
	mv 4-s.txt ./cmp
	./myar -x ar12345.ar 2-s.txt 4-s.txt
	diff ./cmp/2-s.txt 2-s.txt
	diff ./cmp/4-s.txt 4-s.txt

testx: testx12345 testx135 testx24

testd: rejuve testcreate
	cp ar12345.ar ard1.ar
	cp ar12345.ar myard1.ar
	ar d ard1.ar 1-s.txt
	./myar -d myard1.ar 1-s.txt
	cp ar12345.ar ard2.ar
	cp ar12345.ar myard2.ar
	ar d ard2.ar 2-s.txt
	./myar -d myard2.ar 2-s.txt
	cp ar12345.ar ard3.ar
	cp ar12345.ar myard3.ar
	ar d ard3.ar 3-s.txt
	./myar -d myard3.ar 3-s.txt
	cp ar12345.ar ard4.ar
	cp ar12345.ar myard4.ar
	ar d ard4.ar 4-s.txt
	./myar -d myard4.ar 4-s.txt
	cp ar12345.ar ard5.ar
	cp ar12345.ar myard5.ar
	ar d ard5.ar 5-s.txt
	./myar -d myard5.ar 5-s.txt
	diff ard1.ar myard1.ar
	diff ard2.ar myard2.ar
	diff ard3.ar myard3.ar
	diff ard4.ar myard4.ar
	diff ard5.ar myard5.ar
	
		
tests: testq testt testv testx testd

rejuve:
	cp -p ./texts/1-s.txt ./
	cp -p ./texts/2-s.txt ./
	cp -p ./texts/3-s.txt ./
	cp -p ./texts/4-s.txt ./
	cp -p ./texts/5-s.txt ./
	
archivetext:
	rm -fr archive
	mkdir archive
	mv -f 1-s.txt ./archive
	mv -f 2-s.txt ./archive
	mv -f 3-s.txt ./archive
	mv -f 4-s.txt ./archive
	mv -f 5-s.txt ./archive

clean:
	rm -f $(PROGS) *.o *~ *# *.ar *ctoc.txt *vtoc.txt ~.txt
	rm -fr archive
	rm -fr cmp

