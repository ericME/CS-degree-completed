\* test.lp *\
Minimize
value: t

Subject To
cond0: 3 X1 + 2 X2 - 5 X3 <= 8
cond1: X1 <= t
cond2: X2 <= t
cond3: X3 <= t

Bounds
X1 >= 0
X2 >= 0
X3 >= 0


End
