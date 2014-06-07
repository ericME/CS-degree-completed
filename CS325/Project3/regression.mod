
param n, integer, >=2;
set N, default{1..n};
param x{N};
param y{N};

var e{N}, >=0;
var a;
var b;

minimize error: sum{i in N} e[i];

s.t. ub{i in N}: e[i] >= a*x[i]+b -y[i];

s.t. lb{i in N}:  e[i] >= -1 * (a*x[i]+b -y[i]);

solve;

display a,b,error;

data;

param n :=4;

param : N : x y :=
	1   0 0
	2   1 1
	3   2 4
	4   3 9;
