#!/usr/bin/python
#Written and tested in python 3.3.4 on linux 3.13.5-1-ARCH
#Eric Rouse
#Travelling Salesperson Problem solver
#usage:
#   python myTSPsolver.py name-and-path-of-input-file
#example:
#   python myTSPsolver.py test-file-1.txt

#sources:
#Wikipedia TSP: http://en.wikipedia.org/wiki/Travelling_salesman_problem
#stack overflow: http://stackoverflow.com/questions/7159259/optimized-tsp-algorithms
#Wikipedia Prim: http://en.wikipedia.org/wiki/Prim%27s_algorithm
#Wikipedia Hamilton: http://en.wikipedia.org/wiki/Hamiltonian_path and http://en.wikipedia.org/wiki/Hamiltonian_circuit
#Matching: http://mathworld.wolfram.com/PerfectMatching.html
#Piazza Post: https://piazza.com/class/hp5ugh2jc1v21u?cid=167


import signal
import sys
import atexit
import time
import math
import itertools
from collections import defaultdict

output_file = ""
output_length = 0
output_list = []

# Treat each city as  "Node"
# n = name (a number in our case)
# x = euclid x coord
# y = euclid y coord
class Node:
    def __init__(self,n,x,y):
        self.n = n
        self.x = x
        self.y = y

# The signal handler. On receiving sigterm, it writes
# the latest result to the file.
def sig_term(num, frame):
    save_output()
    sys.exit(0)

# The minimum spanning tree function using Prim's algorithm
def mst(cities):
    mst = []

    if len(cities)==0:
        return mst
    

    city_initial = cities[0]
    temp = cities[1:]
    for city in temp: 
        city.d = dist(city,city_initial)
        city.pred = city_initial

    while temp != []:
        min_d = 1e20
        for city in temp:
            if city.d < min_d:
                min_d = city.d
                closest_city = city
        temp.remove(closest_city)
        city_initial = closest_city
        city_next = closest_city.pred
        mst.append((city_initial,city_next))
        for city in temp:
            d = dist(city,closest_city)
            if d<city.d:
                city.d = d
                city.pred = closest_city

    return mst

# The euler tour technique function
# REQUIRES SORTED EDGE LIST!!!
def ett(edge_list):
    tour = []

    current_vertex = edge_list[0][0]
    tour.append(current_vertex)

    while len(edge_list) > 0:
        for edge in edge_list:
            if current_vertex in edge:
                if edge[0] == current_vertex:
                    current_vertex = edge[1]
                else:
                    current_vertex = edge[0]

                edge_list.remove(edge)
                tour.insert(0,current_vertex)
                break
        else:
            return False
    return tour

# The TSP using Christophides Algorithm
def tsp(cities):
    cities_bak = cities[:]
    global output_list
    global output_length
    tsp_output_length = 1e20
    #generate all swap combinations
    els = [list(x) for x in itertools.combinations(range(len(cities)), 2)]
    for e in els:
        # Create a minimum spanning tree
        cities_mst = mst(cities)
        # #print (cities[0].n)
        # Add the reverse paths [convert (u,v) to (v,u)] to the mst
        reverse_cities = []
        for city in cities_mst:
            reverse_cities.append((city[1],city[0]))
        # Sort the MST 
        cities_mst = sorted(cities_mst, key=lambda edge: edge[0].n)
        # Put the MST and reverse MST together into an "master edge list"
        cities_mst += reverse_cities

        #DEBUG PRINTING
        # for edge in cities: #debug
        #     print (edge[0].n, edge[1].n, dist(edge[0],edge[1])) #debug
        
        # Form an Eulerian circuit
        tour = ett(cities_mst)
        # Make the circuit Hamiltonian by skipping visited nodes (shortcutting)
        if tour != False:
            tour_hamilton = []
            tsp_output_list = []
            for edge in tour:
                 if edge not in tour_hamilton:
                    tsp_output_list.append(edge.n)
                    tour_hamilton.append(edge)
                    #print(edge.n) #debug
            temp_len = lent(tour_hamilton)
            if temp_len < tsp_output_length:
                tsp_output_length = temp_len
                output_list = tsp_output_list[:]
                output_length = tsp_output_length
        # Swap
        cities = cities_bak[:]
        cities[e[0]], cities[e[1]] = cities[e[1]], cities[e[0]]

    save_output()
    print ("best path length found:", tsp_output_length) #debug
    return

# The euclidean distance function
def dist(a,b):
    return round((math.sqrt((a.x-b.x)**2 + (a.y-b.y)**2)))

# The length of tour function for finding a distance of an ETT
def lent(tour):
    distance = 0
    
    for i, node in enumerate (tour[0:]):
        #print (i)
        distance += dist(tour[i-1],node)

    return distance

def save_output():
    with open(output_file, 'w+') as f:
        f.write(str("%i\n" % output_length))
        for line in output_list:
            f.write("%i\n" % line)
        f.close()

if __name__ == '__main__':
    cities = []
    output_list = []
    try:
        # try to read the input file
        input_file = sys.argv[1]
        # update the output file name
        output_file = input_file + ".tour"
        # read the file into a list, strip out newlines
        city_list = [line.rstrip('\n') for line in open(input_file)]
        # sanitize the input and create nodes for each city
        for city in city_list:
            s = city.split()
            cities.append(Node(int(s[0]), int(s[1]), int(s[2])))
            # Register signal handler
        signal.signal(signal.SIGTERM, sig_term)
        # Find a TSP solution using Christophides Algorithm
        tsp(cities)
    except IndexError:
        print ("Need an input file!")
    