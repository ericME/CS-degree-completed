import random
import time
import sys
def arrayGen(n):
	n = int(n)
	ar = []
	for i in range(n):
		ar.append(random.randint(-99, 99))

	return (ar)

def recurse(A, start, stop):
    """Recursion for algorithm3 that only considers implicit slice A[start:stop])."""
    if stop == start:                         # zero elements
        return (0, 0, 0)               
    elif stop == start + 1:                   # one element
        if A[start] > 0:
            return (A[start], start, stop)
        else:
            return (0, start, start)
    else:                                     # two or more elements
        mid = (start + stop) // 2

        # find maximum sum(A[i:mid]) for i < mid
        total = 0
        lmax = (0, mid)                       # (t,i) such that sum(A[i:mid]) = t
        for i in range(mid-1, start-1, -1):
            total += A[i]
            if total > lmax[0]:
                lmax = (total,i)
                
        # find maximum sum(A[mid:j]) for j > mid
        total = 0
        rmax = (0, mid)                       # (t, j) such that sum(A[mid:j]) = t
        for j in range(mid+1, stop+1):
            total += A[j-1]
            if total > rmax[0]:
                rmax = (total,j)

        overlay = (lmax[0]+rmax[0], lmax[1], rmax[1])

        return max(recurse(A, start, mid),
                   recurse(A, mid, stop),
                   overlay)

def algorithm3(A):
    """A divide-and-conquer approach achieving O(n log n) time.

    We find the maximum solution from the left half, the maximum from the right,
    and the maximum solution that straddles the middle.  One of those three is
    the true optimal solution.

    Returns tuple designating optimal (maxsum, start, stop).
    """
    return recurse(A, 0, len(A))



if __name__ == "__main__":
	ar = arrayGen(sys.argv[1])
	time1 = time.time()
	r = algorithm3(ar)
	time2 = time.time()
	print((time2-time1)*1000, r)