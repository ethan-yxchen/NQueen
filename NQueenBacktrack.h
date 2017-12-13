#ifndef NQUEENBACKTRACK_H
#define NQUEENBACKTRACK_H

#include <climits>
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class NQueenBacktrack {
private:
    const int numOfQueen;
    // board[i] means there is a queen at (row,col) = (board[i], i)
    // there won't be any conflict in the col if we store the status like this.
    vector<int> board;
    // conflictSet[i] gives a set of spots at col=i that are invalid to place new queen
    vector<unordered_set<int>> conflictSet;
    int numOfSolutions;
    int numOfBk;
    int mrvCol;
    int numOfMRV;
    int isValid(const int &checkRow, const int &checkCol);
    bool placeQueen(int placeRow, int placeCol);
public:
    NQueenBacktrack(int N): numOfQueen(N), board(N, INT_MIN), conflictSet(N),
                              numOfSolutions(0), numOfBk(0), mrvCol(0), numOfMRV(N){}
    int getNumOfBk();
    bool btRecursion(int currCol);
    void btIter();
    void FCMRV();
    void printASolution();
};

#endif /* NQUEENBACKTRACK_H */

