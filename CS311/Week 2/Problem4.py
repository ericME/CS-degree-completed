import os
import shlex
import getopt
import sys


def nth_prime(n):
    #define and iniitalize our return values; 2 is the first prime and is a trivial case
    primes = []
    primes_found = 0
    k = 2;
    #only work from 3 up to n
    while(primes_found < n):
        #define new primes
        found = True
        for m in primes:
            if k % m == 0:
                found = False
                break
        if found:
            primes.append(k)
            primes_found += 1
        k += 1
    return primes[n-1]

if __name__ == '__main__':
    try:
        n = int(sys.argv[1])
        print nth_prime(n)
    except IndexError:
        print "Need an argument, hoss!"
    except ValueError:
        print "Need an integer, hoss!"
