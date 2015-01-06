all:
	g++ ftpserve.cpp -g -Wall -ansi -o ftpserve
	cc ftpclient.c -g -o ftpclient

rmcopy:
	rm -f *.copy
clean:
	rm -f ftpclient ftpserve *.out *.copy
	rm -rf *.dSYM
