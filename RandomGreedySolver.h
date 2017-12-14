class RandomGreedySolver : public SmartSelectSwapSolver {
public:
    vector<int> tmp;
    RandomGreedySolver(int NQ) : SmartSelectSwapSolver(NQ) {}

    int random_step() {
        int delta;
        if (unsolved_list.size() > 500)
            delta = random_greedy();
        else
            delta = random_step_smart_soft();
        steps += delta;
        return delta;
    }

    int random_greedy() {
        int sum(0);

        // remove influence from bins
        for (int col: unsolved_list) {
            int Q = board[col];
            sum -= (--bin_anti_diag[Q + col]);
            sum -= (--bin_diag[Q + NQ - col]);
            is_unsolve[col] = false;
        }

        // magic reassign
        int pool = unsolved_list.size() - 1;
        int step = 0;
        tmp.clear();
        tmp.reserve(unsolved_list.size());
        swap(tmp, unsolved_list);
        for (int i = 0, e = pool - 100; i < e; ++i) {
            uniform_int_distribution<int> dist(i+1, pool);
            int col1 = tmp[i], Q;

            for (int greedy_attempts = 0; greedy_attempts < 30; ++greedy_attempts) {     // like init_magic // random greedy
                int j = dist(generator);
                int col2 = tmp[j];
                attempts++;
                Q = board[col2];
                if (bin_anti_diag[Q + col1] + bin_diag[Q + NQ - col1] == 0) {
                    board[col2] = board[col1];
                    board[col1] = Q;
                    step++;
                    break;
                }
            }

            Q = board[col1];
            sum += update(Q + col1, bin_anti_diag, col1, resident_anti_diag);
            sum += update(Q + NQ - col1, bin_diag, col1, resident_diag);
        }

        for (int i = max(0, pool-100); i <= pool; ++i) {
            attempts++;
            int col = tmp[i];
            int Q = board[col];
            sum += update(Q + col, bin_anti_diag, col, resident_anti_diag);
            sum += update(Q + NQ - col, bin_diag, col, resident_diag);
        }

        if (verbose & 8) {
            printf("next batch #unsolved[%ld] ", unsolved_list.size());
            printf(" #conflict[%d] sum[%d]\n", conflicts, sum);
        }

        conflicts += sum;

        return step;
    }

};
