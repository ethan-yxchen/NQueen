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

bool NQueenBacktrack::placeQueen(int placeRow, int placeCol) {
//    for (int col = 0; col < numOfQueen; ++col) {
//        if (board[col] == INT_MIN) continue;
//        int row = board[col];
//        conflictSet[placeCol].insert(row);
//    }           
    numOfMRV = numOfQueen;
    for (int row = 0; row < numOfQueen; ++row)
        conflictSet[placeCol].insert(row);
    for (int col = 0; col < numOfQueen; ++col) {
        if (col == placeCol) continue;
        for (int row = 0; row < numOfQueen; ++row) {
            if (row == placeRow || abs(col - placeCol) == abs(row - placeRow))
                conflictSet[col].insert(row);
        }
        // update the MRV column (minimum available spot)
        int available = numOfQueen - conflictSet[col].size();
        if (available < numOfMRV && available > 0) {
            mrvCol = col;
            numOfMRV = available;
        }
    }
    if (numOfMRV == numOfQueen) // all col has 0 remaining value
        return false;
    else {
        board[placeCol] = placeRow;
        printf("Place queen at (%d, %d), ", placeRow, placeCol);
        printf("MRV col is %d, MRV = %d\n", mrvCol, numOfMRV);
        return true;
    }
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
    int row = 0, col = 0;
    while (col < numOfQueen) {
        while (row < numOfQueen) {
            if(isValid(row, col)) {
                board[col] = row;
                // reset the col for backtracking or searching valid spot in next row
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
            // backtrack
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

void NQueenBacktrack::FCMRV() {
    
    placeQueen(1, 3);
    placeQueen(0, 3);
    
    placeQueen(1, 2);
    placeQueen(3, 2);
    
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