import itertools


lst = range(10)
combs = []
print (lst)
print ("*"*10)

els = [list(x) for x in itertools.combinations(lst, 2)]


print (els)