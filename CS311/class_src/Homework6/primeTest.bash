#!/bin/bash
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #6
#
# make sure we have the freshest possible build
make clean
make

#test 1,000,000 primes - primePThread
echo "testing 1000000 primes"
./primePThread -m 1000000 -c 5 > ./1000000.pthread
./primeMProc -m 1000000 -c 5 > ./1000000.mproc
sleep 5
diff ./1000000.primes ./1000000.pthread
diff ./1000000.primes ./1000000.mproc

echo "finished testing 1000000 primes"

#prime p thread timings

/usr/bin/time -p -o ./c30.pthread ./primePThread -q -m 100000000 -c 30
/usr/bin/time -p -o ./c25.pthread ./primePThread -q -m 100000000 -c 25
/usr/bin/time -p -o ./c20.pthread ./primePThread -q -m 100000000 -c 20
/usr/bin/time -p -o ./c15.pthread ./primePThread -q -m 100000000 -c 15
/usr/bin/time -p -o ./c10.pthread ./primePThread -q -m 100000000 -c 10
/usr/bin/time -p -o ./c8.pthread ./primePThread -q -m 100000000 -c 8
/usr/bin/time -p -o ./c6.pthread ./primePThread -q -m 100000000 -c 6
/usr/bin/time -p -o ./c5.pthread ./primePThread -q -m 100000000 -c 5
/usr/bin/time -p -o ./c4.pthread ./primePThread -q -m 100000000 -c 4
/usr/bin/time -p -o ./c3.pthread ./primePThread -q -m 100000000 -c 3
/usr/bin/time -p -o ./c2.pthread ./primePThread -q -m 100000000 -c 2
/usr/bin/time -p -o ./c1.pthread ./primePThread -q -m 100000000 -c 1

/usr/bin/time -p -o ./c30.mproc ./primeMProc -q -m 100000000 -c 30
/usr/bin/time -p -o ./c25.mproc ./primeMProc -q -m 100000000 -c 25
/usr/bin/time -p -o ./c20.mproc ./primeMProc -q -m 100000000 -c 20
/usr/bin/time -p -o ./c15.mproc ./primeMProc -q -m 100000000 -c 15
/usr/bin/time -p -o ./c10.mproc ./primeMProc -q -m 100000000 -c 10
/usr/bin/time -p -o ./c8.mproc ./primeMProc -q -m 100000000 -c 8
/usr/bin/time -p -o ./c6.mproc ./primeMProc -q -m 100000000 -c 6
/usr/bin/time -p -o ./c5.mproc ./primeMProc -q -m 100000000 -c 5
/usr/bin/time -p -o ./c4.mproc ./primeMProc -q -m 100000000 -c 4
/usr/bin/time -p -o ./c3.mproc ./primeMProc -q -m 100000000 -c 3
/usr/bin/time -p -o ./c2.mproc ./primeMProc -q -m 100000000 -c 2
/usr/bin/time -p -o ./c1.mproc ./primeMProc -q -m 100000000 -c 1
echo "brace yourself, winter is coming, this will take awhile"
/usr/bin/time -p -o ./unitmaxc30.pthread ./primePThread -q -c 30
/usr/bin/time -p -o ./unitmaxc30.mproc ./primeMProc -q -c 30
#a little encouragement
echo "ALL TESTS COMPLETE ... IF DIFF ERRORS NOT REPORTED YOU MAY SLEEP NOW!!"