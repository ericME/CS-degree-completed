
param n, integer, >=2;
set N, default{1..n};
param x{N};
param y{N};

var z{N}, >=0;
var a;
var b;
var c;

minimize error: sum{i in N} z[i];

s.t. ub{i in N}: z[i] >= a*x[i] + b - y[i];

s.t. lb{i in N}:  z[i] >= -1 * (a*x[i] + b - y[i]);

solve;

display a,b,error;

data;

param n :=7;

param : N : x y :=
	1   1 3
	2   2 5
	3   3 7
	4   5 11
	5   7 14
	6   8 15
	7   10 19;
