#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #6
#

import os
import shlex
import getopt
import sys
import math


def primes_to(n):
    #define and iniitalize our return values; 2 is the first prime and is a trivial case
    primes = []
    primes_found = 0
    k = 2;
    #only work from 3 up to n
    while(k < n):
        #define new primes
        found = True
        for m in primes:
            if k % m == 0:
                found = False
                break
        if found:
            primes.append(k)
            print k
        k += 1
    return

if __name__ == '__main__':
    try:
        n = int(sys.argv[1])
        primes_to(n)
    except IndexError:
        print "Need an argument, hoss!"
    except ValueError:
        print "Need an integer, hoss!"
