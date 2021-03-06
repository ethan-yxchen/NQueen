#ifndef NQUEENBACKTRACK_H
#define NQUEENBACKTRACK_H

#include <climits>
#include <random>
#include <chrono>
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
    unordered_set<int> unAssigned;
    unsigned int seed;
    mt19937 generator;
    int isValid(const int &checkRow, const int &checkCol);
    void placeQueen(int row, int col) {board[col] = row; unAssigned.erase(col); updateConflict(); /*printf("Placed (%d, %d)\n", row, col);*/}
    void removeQueen(int row, int col) {board[col] = INT_MIN; unAssigned.insert(col); updateConflict(); /*printf("Removed (%d, %d)\n", row, col);*/}
    void updateConflict();
    bool fwdCheck();
    int findMRVCol();
    bool fcMrvRecursion(int planCol);
    void fcMrvIter();
public:
    long numOfBk;
    long numOfNodes;
    NQueenBacktrack(int N): numOfQueen(N), board(N, INT_MIN), conflictSet(N),
                              seed(chrono::system_clock::now().time_since_epoch().count()),generator(seed),
                              numOfBk(0), numOfNodes(0) {
        for (int col = 0; col < numOfQueen; ++col)
            unAssigned.insert(col);
    }
    bool btRecursion(int currCol);
    void btIter();
    void fcMrv();
    void printASolution();
    bool verify_conflict();
    bool verify_solution() const;
    void selfTest();
};

#endif /* NQUEENBACKTRACK_H */

