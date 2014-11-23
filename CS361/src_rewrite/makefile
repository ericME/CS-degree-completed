all: matchDonor



matchDonor: matchDonor.o

	gcc -g -Wall -std=c99 -o matchDonor matchDonor.o


matchDonor.o: matchDonor.c

	gcc -g -Wall -std=c99 -c matchDonor.c


clean:

	rm matchDonor.o
	rm matchDonor

