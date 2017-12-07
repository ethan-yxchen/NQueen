#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <string>

using namespace std;


class NQueenSwapSolver {
public:
    int NQ;
    vector<int> board;
    vector<int> bin_diag;
    vector<int> bin_anti_diag;
    unsigned int seed;
    mt19937 generator;
    uniform_int_distribution<int> distribution;
    int conflicts;
    bool conflicts_dirty;
    int soft_threshold;
    int prob_plateau;
        
    NQueenSwapSolver(int N) : NQ(N), board(N),
        bin_diag(2*N), bin_anti_diag(2*N),
        seed(chrono::system_clock::now().time_since_epoch().count()),
        generator(seed), distribution(0, N - 1),
        conflicts(0), conflicts_dirty(true),
        soft_threshold(0), prob_plateau(3) {
    }

    void init() {
        for (int i = 0; i < NQ; ++i)
            board[i] = i;
        
        init_random();
    }

    void init_random() {
        for (int i = 0, e = NQ - 1; i < e; ++i) {
            uniform_int_distribution<int> dist(i, e);
            int j = dist(generator);
            if (i != j)
                swap(board[i], board[j]);
        }
    }
    
    bool random_step() {
        return random_step_soft();
    }

    bool random_step_soft() {
        if (conflicts_dirty) { calculate_conflict(); }

        int i = distribution(generator);
        int j = distribution(generator);
        while (i == j)
            j = distribution(generator);
        
        return swap_soft(i, j);
    }
    
    bool swap_soft(int col1, int col2) {
        int cost = diff(col1, col2);
        
        /**
         * soft margin: even if cost > 0, by a exponential probability,
         * swap col1, col2
         */
        if (cost > 0) {
            if(conflicts >= soft_threshold)
                return false;
            if (uniform_int_distribution<int>(0, 1<<cost)(generator))
                return false;
        }
        
        if (cost == 0)
            if (uniform_int_distribution<int>(0, prob_plateau)(generator))
                return false;
        
        swap_row(col1, col2);
        conflicts += cost;
        return true;
    }

    void calculate_conflict() {
        int sum = 0;
        conflicts_dirty = false;

        for (int i = 0, e = NQ*2; i < e; ++i)
            bin_diag[i] = bin_anti_diag[i] = 0;
        
        for (int col = 0, e = NQ; col < e; ++col) {
            int Q = board[col];
            sum += bin_anti_diag[Q + col]++;   // 0 ~ 2N - 2
            sum += bin_diag[Q + NQ - col]++;   // 1 ~ 2N - 1
        }
        
        conflicts = sum;
    }

    int diff(int col1, int col2) const {        
        int Q1 = board[col1];
        int Q2 = board[col2];
        int _;
        int rcol1 = NQ - col1;
        int rcol2 = NQ - col2;
        
        _ = bin_anti_diag[Q1 + col2] + bin_diag[Q1 + rcol2] +
            bin_anti_diag[Q2 + col1] + bin_diag[Q2 + rcol1];
        _ -= bin_anti_diag[Q1 + col1] + bin_diag[Q1 + rcol1] +
            bin_anti_diag[Q2 + col2] + bin_diag[Q2 + rcol2] - 4;

        int Q = Q1 - Q2;
        int C = col1 - col2;
        if (Q == C || -Q == C) { _ += 2; }
        
        return _;
    }
    
    void swap_row(int col1, int col2) {
        int Q1 = board[col1];
        int Q2 = board[col2];
        int rcol1 = NQ - col1;
        int rcol2 = NQ - col2;
        board[col1] = Q2;
        board[col2] = Q1;
        --bin_anti_diag[Q1 + col1];
        --bin_anti_diag[Q2 + col2];
        ++bin_anti_diag[Q1 + col2];
        ++bin_anti_diag[Q2 + col1];
        --bin_diag[Q1 + rcol1];
        --bin_diag[Q2 + rcol2];
        ++bin_diag[Q1 + rcol2];
        ++bin_diag[Q2 + rcol1];
    }

};

