#pragma once

#include <vector>
#include <cstdio>
#include <chrono>

using namespace std;


template <class Solver>
class LocalSearchRunner {

public:
    Solver solver;
    int NQ;
    uint64_t steps, attempts;
    chrono::duration<double> elapse;

    LocalSearchRunner(int NQ) : solver(NQ), NQ(NQ), steps(0), attempts(0) {}
    
    void run(int verbose=0) {
        auto start = chrono::system_clock::now();
        solver.verbose = verbose;
        verbose &= 2;
        
        solver.init();
        if (verbose)
            printf("N=%d seed=%d\n", NQ, solver.seed), print_board();
        solver.calculate_conflict();
        
        uint64_t limit = NQ * 1000;
        while( solver.conflicts && solver.attempts < limit) {
            steps += solver.random_step();
        }
        if (verbose)
            print_board();
        
        steps = solver.steps;
        attempts = solver.attempts;
        auto end = chrono::system_clock::now();
        elapse = end-start;
        elapse *= 1000000;
    }
    
    bool verify_solution() const {
        auto &board = solver.board;
        int NQ = NQ;
        
        auto row = [&board, &NQ](int col) { return board[col]; };
        auto diag = [&board, &NQ](int col) { return board[col] + col; };
        auto adiag = [&board, &NQ](int col) { return board[col] + NQ - col; };
        
        auto test = [&NQ](vector<bool> &bins, decltype(row) proj) {
            for (int col = 0; col < NQ; ++col) {
                int b = proj(col);
                if (bins[b])
                    return false;
                
                bins[b] = true;
            }
            return true;
        };
        
        return test(vector<bool>(NQ, false), row) &&
               test(vector<bool>(NQ+NQ, false), diag) &&
               test(vector<bool>(NQ+NQ, false), adiag);
    }
    
    void print_board() const {
        string line(NQ, '.');
        printf("--\n");
        for (int i = 0; i < NQ; ++i) {
            int Q = solver.board[i];
            line[Q] = 'Q';
            printf("%s  %*d %*d\n", line.c_str(), 5, i + Q, 5, NQ - i + Q);
            line[Q] = '.';
        }
    }
    
    void stats() const {
        printf("#steps[%*ld]  ", 11, steps);
        printf("#attempts[%*ld]  ", 11, attempts);
        printf("#conflict[%*d]  ", 11, solver.conflicts);
        printf("#time[%*.3f]  ", 11, elapse.count());
        printf("\n");
    }
    
    void dump_bins() const {
        for (int i = 0; i < NQ+NQ; ++i)
            printf("%d ", solver.bin_diag[i]);
        printf("\n");
        for (int i = 0; i < NQ+NQ; ++i)
            printf("%d ", solver.bin_anti_diag[i]);
        printf("\n");
    }

};
