# Tic-Tac-Toe-Application-by-Using-Threads

In my code, I used coarse-grained lock. It is used for mark the cell operations. Both threads mark
their cells in the same critical section. A variable is used so that two threads can mark the cells in
order. The value of this variable is set as zero at the beginning. When it is zero, first thread mark a
cell and set count value as 1. When it is one, second thread mark a cell and set count value as 0.
