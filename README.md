# NQueen

*How to make:
1. Unzip the code.zip
2. Go to the folder NQueen, run "make all"


*How to run:
1. After make, run the program by
./nqueen arg1 arg2 arg3 arg4 arg5 arg6 arg7

noticed that if arg6==3, only arg1 matters (backtrack sovler only takes arg1 and arg6)
Please don't try N>100 for backtracking search.
arg1: N queens
arg2: repeat N times
arg3: stimulated annealing soft_threshold, 0 means turnnig off
arg4: if in plateau, there is a probablity of 1/(2^(arg3-1)+1) to do swap_soft
arg5: verbose level (bits)
arg6: select solver (0:NQueenSwapSolver 1: SmartSelectSwapSolver 2: RandomGreedySolver 3: Backtrack (ORG and BT+FC+MRV) )
arg7: output path, skip if don't want to write output into file