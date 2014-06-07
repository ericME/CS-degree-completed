#####
#This file contains three types of algorithms
#for determining the maximum sub array of a given array
#Resources:
#http://cs.slu.edu/~goldwasser/courses/slu/csci314/2012_Fall/lectures/maxsubarray/
#http://en.wikipedia.org/wiki/Maximum_subarray_problem
#http://en.wikipedia.org/wiki/Divide_and_conquer_algorithm
#https://en.wikibooks.org/wiki/Algorithms/Divide_and_Conquer
#By Eric Rouse
#####

#### Algorithm 1
#### Simple Enumeration


def maxsubarray1(l):
    maxVal = l[0]
    summ = 0
    subArr = 1
    for i in l:
        k = subArr
        
        while k<=len(l):
            summ = 0
            for j in l[subArr:k]:
                summ += j
            
            if i+summ > maxVal:
                maxVal = i+summ
            k += 1
        subArr += 1
    return maxVal
            


#### Algorithm 2
#### Slightly Better Enumeration

def maxsubarray2(l):
    maxVal = l[0]
    summ = 0
    subArr = 1
    for i in l:
        summ = i
        if summ > maxVal:
            maxVal = summ
        for j in l[subArr:]:
            summ += j
            if summ > maxVal:
                maxVal = summ
        subArr += 1
                
    return maxVal

#### Algorithm 3
#### Divide and Conquer

def maxsubarray3(l):
    #zero length array; shouldn't ever happen
    if len(l) == 0:
        return 0
    #single length array, get rid of the negatives
    if len(l) == 1:
        return max(0, l[0])
    
    #find the max starting from the middle and working out
    #to the left and to the right
    
    max_left = 0
    max_right = 0
    mid_left = len(l)/2
    mid_right = mid_left + 1
    for i in range(0, mid_left):
        sum_left = sum(l[(mid_left-i):mid_left+1])
        sum_right = sum(l[mid_right:(mid_right+i+1)])
        if sum_left > max_left:
            max_left = sum_left
        if sum_right > max_right:
            max_right = sum_right
            
    #this is the magic bit
    return max(max(maxsubarray3(l[:mid_left]),maxsubarray3(l[mid_left:])),max_right+max_left)


