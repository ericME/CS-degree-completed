from time import time
import random
import Enumeration as enum

#build a random array
random.seed()
l = []
sizes = [100,200,300, 400, 500, 600, 700, 800, 900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000]


for size in sizes:
    #make an array of random integers
    print size
    for i in range(size):
        l.append(random.randrange(-99,99,1))

    #keep it from taking too long
    if size <= 900:
        #time for the first algorithm
        for i in range(10):
            start = time()
            enum.maxsubarray1(l)
            end = time()
            total = end - start

        print total/10

    #time for the second algorithm
    for i in range(10):
        start = time()
        enum.maxsubarray2(l)
        end = time()
        total = end - start

    print total/10

    #time for the third algorithm
    for i in range(10):
        start = time()
        enum.maxsubarray3(l)
        end = time()
        total = end - start

    print total/10
    print
