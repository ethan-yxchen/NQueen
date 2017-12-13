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
    int verbose;
    uint64_t steps;
    uint64_t attempts;

    NQueenSwapSolver(int N) : NQ(N), board(N),
        bin_diag(2*N), bin_anti_diag(2*N),
        seed(chrono::system_clock::now().time_since_epoch().count()),
        //seed(1971311498),
        generator(seed), distribution(0, N - 1),
        conflicts(0), conflicts_dirty(true),
        soft_threshold(0), prob_plateau(3),
        steps(0), attempts(0) {
    }

    void init() {
        for (int i = 0; i < NQ; ++i)
            board[i] = i;
        // init_magic(NQ - get_limit(NQ));
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

    int get_limit(int N)
    {
        if (N <= 10)
                return (N>8)?8:N;
        else if (N < 100)
                return N;
        else if (N < 1000)
                return 30;
        else if (N < 10000)
                return 50;
        else if (N < 100000)
                return 80;
        else
                return 100;
    }

    void init_magic(int no_coflict_limit) {
        // clock_t start, finish;
        // start = clock();

        for (int i = 0, e = NQ*2; i < e; ++i)
            bin_diag[i] = bin_anti_diag[i] = 0;

        for (int col = 0; col < no_coflict_limit; ++col) {
            uniform_int_distribution<int> dist(col+1, NQ-1);
            int victim_row, victim_col;
            do {
                victim_col = dist(generator);
                victim_row = board[victim_col];
            } while ((bin_anti_diag[victim_row + col] + bin_diag[victim_row + NQ - col]) != 0); // until find no conflict

            swap(board[col], board[victim_col]);
            ++bin_anti_diag[board[col] + col];
            ++bin_diag[board[col] - col + NQ];
        }
        for (int col = no_coflict_limit; col < NQ - 1; ++col) {
            uniform_int_distribution<int> dist2(col+1, NQ-1);
            int victim_col = dist2(generator);
            swap(board[col], board[victim_col]);
        }
        // finish = clock();
        // printf("no_conflict_limit = %d\n", no_coflict_limit);
         // printf("init time  = %-5.3g\n",(double)(finish - start) / CLOCKS_PER_SEC);
    }

    int random_step() {
        int delta = random_step_soft();
        steps += delta;
        return delta;
    }

    int random_step_soft() {
        if (conflicts_dirty) { calculate_conflict(); }

        int i = distribution(generator);
        int j = distribution(generator);
        while (i == j)
            j = distribution(generator);

        return swap_soft(i, j)? 1 : 0;
    }

    bool swap_soft(int col1, int col2) {
        int cost = diff(col1, col2);
        attempts++;

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

    virtual void calculate_conflict() {
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

    virtual void swap_row(int col1, int col2) {
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

