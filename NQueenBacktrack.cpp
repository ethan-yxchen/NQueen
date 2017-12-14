#include <future>

#include "NQueenBacktrack.h"

int NQueenBacktrack::isValid(const int &checkRow, const int &checkCol) { 
    for (int col = 0; col < checkCol; ++col) {
        /*  
         * 1. The queen on the column board[row] conflicts to the passed-in checkRow when board[row] == checkCol
         * 2. If one of the placed queen conflicts to new queen in diagonal,
         *    the difference between row index and column index of these two queens are the same
         */
        if (board[col] == checkRow || abs(col - checkCol) == abs(board[col] - checkRow))
            return 0;
    }
    return 1;
}

void NQueenBacktrack::updateConflict() {
    for (int scanCol = 0; scanCol < numOfQueen; ++scanCol) {
        int scanRow = board[scanCol];
        // col has no queen yet
        if (scanRow == INT_MIN) continue;
        // mark every spot that conflict with (board[col], col)
        for (int col = 0; col < numOfQueen; ++col) {            
            if (col == scanCol) {
                for (int row = 0; row < numOfQueen; ++row)
                    conflictSet[col].insert(row);
            }
            else {
                for (int row = 0; row < numOfQueen; ++row)
                    if (row == scanRow || abs(col - scanCol) == abs(row - scanRow))
                        conflictSet[col].insert(row);
            }
        }
    }
}

bool NQueenBacktrack::fwdCheck() {
    if (unAssigned.size() == 0)
        return false;
    for (auto col: unAssigned)
        if (conflictSet[col].size() == numOfQueen)
            return false;
        else
            return true;
}

// find MRV column (minimum available spot)
int NQueenBacktrack::findMRVCol() {
    int numOfMRV = numOfQueen, mrvCol;
    for (int col = 0; col < numOfQueen; ++col) {        
        int available = numOfQueen - conflictSet[col].size();
        if (available < numOfMRV && available > 0) {
            mrvCol = col;
            numOfMRV = available;
        }
    }
    if (numOfMRV == numOfQueen) // all col has 0 remaining value
        mrvCol = -1;
//    printf ("mrvCol = %d, mrv = %d\n", mrvCol, numOfMRV);
    return mrvCol;
}

bool NQueenBacktrack::fcMrvRecursion(int planCol) {
    bool isSafe = false;
    if (this->unAssigned.empty()) {
        isSafe = true;
    }
    else {
        // still have unAssigned but all spot are invalid
        if (planCol < 0) {
            numOfBk++;
            return false;
        }            
        for (int planRow = 0; planRow < numOfQueen; ++planRow) {
             // if planRow is marked as conflict
            if (conflictSet[planCol].find(planRow) != conflictSet[planCol].end())
                continue;
            placeQueen(planRow, planCol);
            if (!fwdCheck())
                break;  // return false, backtrack
            int nextCol = findMRVCol();
            isSafe = btRecursion(nextCol);
            if (isSafe)
                return true;
            else
                removeQueen(planRow, planCol);
        }
        numOfBk++;
    }
    return isSafe;
}

int NQueenBacktrack::getNumOfBk() {
    return numOfBk;
}

bool NQueenBacktrack::btRecursion(int currCol) {
    bool isSafe = false;
    if (currCol >= numOfQueen) {
        isSafe = true;
        ++numOfSolutions;
    }
    else {
        for (int sRow = 0; sRow < numOfQueen; ++sRow) {
            if (isValid(sRow, currCol)) {
                board[currCol] = sRow;
                isSafe = btRecursion(currCol+1);
                if (isSafe) {
                    return true;
                }
                else
                    board[currCol] = INT_MIN;
            }
        }
        numOfBk++;
    }
    return isSafe;
}

void NQueenBacktrack::btIter() {
    numOfBk = 0;
    int row = 0, col = 0;
    while (col < numOfQueen) {
        while (row < numOfQueen) {
            if(isValid(row, col)) {
                board[col] = row;
                // reset the col for backtracking or searching valid spot in next col
                row = 0;
                break;  
            }  
            else
                ++row;
        }

        if(board[col] == INT_MIN) {
            // no way to backtrack, no solution found (impossible in N queens problem, but in case)
            if (col == 0)
                break;
            else {
                numOfBk++;
                --col;
                // move the queen in last col to next row
                row = board[col] + 1;
                // clean the queen in last col
                board[col] = INT_MIN;
                continue;
            }  
        }
        // reached last col, which means a solution is found.
        if (col == numOfQueen - 1) {
            ++numOfSolutions;
            return;
        }  
        // if not, search for next col
        ++col;
    }  
}

void NQueenBacktrack::fcMrv() {
    uniform_int_distribution<int> distribution(0, numOfQueen-1);
    int startCol = distribution(generator);
    fcMrvRecursion(startCol);
}

void NQueenBacktrack::printASolution() {  
    if (numOfQueen > 100) {
        cout<<"Do not print the result with more than 100 Queens"<<endl;
        return;
    }

    cout<<"Solution count:"<<numOfSolutions<<endl;
    int row, col;
    for (row = 0; row < numOfQueen; ++row) {  
        for (col = 0; col < numOfQueen; ++col) {  
            // the board[row] doesn't match the traversed column, which means there's no queen here
            if (board[row] != col) 
                cout<<".";
            else
                cout<<"Q";
        }
        cout<<endl;            
    }
    cout<<"-----------------------------------------------"<<endl;
}

bool NQueenBacktrack::verify_conflict() {
    for (int i = 0; i < numOfQueen; ++i) {
        if (isValid(board[i], i) == 0)
            return false;
    }
    return true;
}
