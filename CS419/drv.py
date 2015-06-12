
def expand(n):
    string = "";
    for i in range(1,n+1):
        string += str(i)
        if i < n:
            string += ","
    string.strip(" ")
    print string

expand(14)
expand(22)
expand(17)
expand(12)
expand(11)
expand(3)