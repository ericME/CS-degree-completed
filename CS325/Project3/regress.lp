\* regress.lp *\
Minimize
value: ZZ

Subject To
z_1U: ZZ + 1 AA + 3 BB - CC  >= 0
z_1L: ZZ - 1 AA - 3 BB + CC  >= 0
z_2U: ZZ + 2 AA + 5 BB - CC  >= 0
z_2L: ZZ - 2 AA - 5 BB + CC  >= 0
z_3U: ZZ + 3 AA + 7 BB - CC  >= 0
z_3L: ZZ - 3 AA - 7 BB + CC  >= 0
z_4U: ZZ + 5 AA +11 BB - CC  >= 0
z_4L: ZZ - 5 AA -11 BB + CC  >= 0
z_5U: ZZ + 7 AA +14 BB - CC  >= 0
z_5L: ZZ - 7 AA -14 BB + CC  >= 0
z_6U: ZZ + 8 AA +15 BB - CC  >= 0
z_6L: ZZ - 8 AA -15 BB + CC  >= 0
z_7U: ZZ +10 AA +19 BB - CC  >= 0
z_7L: ZZ -10 AA -19 BB + CC  >= 0

Bounds
AA >= 0
BB >= 0
CC >= 0
ZZ > 0

End
