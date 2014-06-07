import math

def sieve(n):
    #define and iniitalize our return values
    primes = range(2,n)
    #find the square root of n
    rootn = math.sqrt(n)
    #set k equal to 1
    k = 1;
    #only work from 1 up to square root of n
    while(k < rootn):
        #define new primes as m
        for m in primes:
            #found a prime!
            if m > k:
                #take its multiples out of the list
                for i in range(2,n-k):
                    if m*i in primes: primes.remove(m*i)
        k += 1
    return len(primes), primes


#debug        
print sieve(250)
print '#'*75
print sieve(1000)

