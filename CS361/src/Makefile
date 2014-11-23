CFLAGS=-Wall
LIBS=-lcheck

all: unit_tests

unit_tests: main.o addDonor.o removeDonor.o unit_tests.o
	gcc -o unit_tests main.o addDonor.o unit_tests.o

main.o: main.c addDonor.h removeDonor.h unit_tests.h
	gcc $(CFLAGS) -c main.c

addDonor.o: addDonor.c addDonor.h
	gcc $(CFLAGS) -c addDonor.c

removeDonor.o: removeDonor.c removeDonor.h
	gcc $(CFLAGS) -c removeDonor.c

unit_tests.o: unit_tests.c unit_tests.h
	gcc $(CFLAGS) -c unit_tests.c

test: unit_tests
	./unit_tests

clean:
	rm -f *.o unit_tests