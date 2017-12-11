#pragma once

class SmartSelectSwapSolver : public NQueenSwapSolver {
public:
    vector<int> unsolved_list;
    vector<int> candidate;
    vector<bool> is_unsolve;
    vector<int> resident_diag;
    vector<int> resident_anti_diag;
    SmartSelectSwapSolver(int NQ) : NQueenSwapSolver(NQ),
        is_unsolve(NQ), resident_diag(NQ*2), resident_anti_diag(NQ*2) {}
    
    void add_unsolve(int col) {
        //printf("add_unsolve %d  (%s)\n", col, is_unsolve[col]? "yes" : "no");
        if (is_unsolve[col]) { return; }
        is_unsolve[col] = true;
        unsolved_list.push_back(col);
    }
    
    int update(int diag, vector<int> &bin, int col, vector<int> &resident) {
        int bincount = bin[diag]++;
        if (bincount) {
            add_unsolve(col);
            add_unsolve(resident[diag]);
        }
        resident[diag] = col;
        return bincount;
    }

    virtual void calculate_conflict() {
        int sum = 0;

        unsolved_list.reserve(NQ);
        unsolved_list.clear();
        for (int i = 0, e = NQ*2; i < e; ++i)
            bin_diag[i] = bin_anti_diag[i] = 0;
        
        for (int col = 0, e = NQ; col < e; ++col) {
            is_unsolve[col] = false;
            int Q = board[col];

            sum += update(Q + col, bin_anti_diag, col, resident_anti_diag);
            sum += update(Q + NQ - col, bin_diag, col, resident_diag);
        }
                
        conflicts = sum;
        conflicts_dirty = false;


        if (verbose & 1) {
            printf("calculate_conflict: ");
            printf("#conflicts[%d] ", conflicts);
            printf("#unsolved[%ld]: ", unsolved_list.size());
            //for (int col: unsolved_list) { printf("%d ", col); }
            printf("\n");
        }
    }

    int random_step() {
        int delta = random_step_smart_soft();
        steps += delta;
        return delta;
    }

    inline bool has_conflict(int col) const {
        int Q = board[col];
        return bin_anti_diag[Q + col] > 1 || bin_diag[Q + NQ - col] > 1;
    }

    int random_step_smart_soft() {
        if (conflicts_dirty) { calculate_conflict(); }
        if (candidate.empty()) {
            candidate.reserve(unsolved_list.size());
            for (int i: unsolved_list) {
                is_unsolve[i] = false;
                if (has_conflict(i)) { candidate.push_back(i); }
            }
            if (verbose & 4) {
                printf("next batch #unsolved[%ld] ", unsolved_list.size());
                printf("#candidate[%ld] #conflict[%d]\n", candidate.size(), conflicts);
            }
            unsolved_list.clear();
            if (candidate.empty())
                return 0;
        }

        int i = candidate.back();
        candidate.pop_back();
        int j;
        
        int n = candidate.size();
        if (n <= 5) {
            j = distribution(generator);
            while (i == j)
                j = distribution(generator);
            if (swap_soft(i, j))
                return 1;
        } else {
            for (int _ = 0; _ < 2; ++_) {
                auto u = uniform_int_distribution<int>(0, n-1);
                int k = u(generator);
                j = candidate[k];
                if (swap_soft(i, j))
                    return 1;
            }
        }

        add_unsolve(i);
        return 0;
    }

    virtual void swap_row(int col1, int col2) {
        int Q1 = board[col1];
        int Q2 = board[col2];
//        printf("swap (%d %d) (%d %d) ", col1, Q1, col2, Q2);
//        printf("a(%d %d -> %d %d) ", Q1 + col1, Q2 + col2, Q1 + col2, Q2 + col1);
        board[col1] = Q2;
        board[col2] = Q1;
        --bin_anti_diag[Q1 + col1];
        --bin_anti_diag[Q2 + col2];

        update(Q1 + col2, bin_anti_diag, col2, resident_anti_diag);
        update(Q2 + col1, bin_anti_diag, col1, resident_anti_diag);

        int rcol1 = NQ - col1;
        int rcol2 = NQ - col2;
//        printf("d(%d %d -> %d %d) ", Q1 + rcol1, Q2 + rcol2, Q1 + rcol2, Q2 + rcol1);
        --bin_diag[Q1 + rcol1];
        --bin_diag[Q2 + rcol2];

        update(Q1 + rcol2, bin_diag, col2, resident_diag);
        update(Q2 + rcol1, bin_diag, col1, resident_diag);
//        printf(" conflicts %d\n", conflicts);
    }

};

