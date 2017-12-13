#ifndef NQUEENBACKTRACK_H
#define NQUEENBACKTRACK_H

#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class NQueenBacktrack {
private:
    const int numOfQueen;
    // board[i] means there is a queen at (row,col) = (board[i], i)
    // there won't be any conflict in the col if we store the status like this.
    vector<int> board;
    int numOfSolutions = 0;
    int numOfBk = 0;
    int isValid(const int &checkRow, const int &checkCol);
public:      
    NQueenBacktrack(int N): numOfQueen(N), board(N){
        for (int i = 0; i < numOfQueen; ++i)
            board[i] = INT_MIN;
    }  
    int getNumOfBk();
    bool placeRecurOne(int currCol);
    void placeIter();
    void placeFCMV();
    void printASolution();
};

#endif /* NQUEENBACKTRACK_H */

