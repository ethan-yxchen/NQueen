#include <cassert>

#include "NQueenSwapSolver.h"
#include "BacktrackRunner.h"
#include "LocalSearchRunner.h"
#include "LocalSearchTester.h"
#include "SmartSelectSwapSolver.h"
#include "RandomGreedySolver.h"

int main(int argc, const char *argv[]) {
    int arg = 1;
    int N = (argc > arg)? stoi(string(argv[arg])) : 4;
    arg++;
    int repeat = (argc > arg)? stoi(string(argv[arg])) : 1;
    arg++;
    int soft_threshold = (argc > arg)? stoi(string(argv[arg])) : 2;
    arg++;
    int prob_plateau = (argc > arg)? stoi(string(argv[arg])) : 3;
    arg++;
    int verbose = (argc > arg)? stoi(string(argv[arg])) : 0;
    arg++;
    int solver =  (argc > arg)? stoi(string(argv[arg])) : 2;
    arg++;
    const char *out = (argc > arg)? argv[arg] : nullptr;
    arg++;

    switch (solver) {
        case 0: {
            LocalSearchTester<LocalSearchRunner<NQueenSwapSolver>> tester1(N, repeat, soft_threshold, prob_plateau);
            tester1.test(verbose, out);
            tester1.stats();
            break;
        }
        case 1: {
            LocalSearchTester<LocalSearchRunner<SmartSelectSwapSolver>> tester2(N, repeat, soft_threshold, prob_plateau);
            tester2.test(verbose, out);
            tester2.stats();
            break;
        }
        case 2: {
            LocalSearchTester<LocalSearchRunner<RandomGreedySolver>> tester3(N, repeat, soft_threshold, prob_plateau);
            tester3.test(verbose, out);
            tester3.stats();
            break;
        }
        case 3: {
            BacktrackRunner runner;
            runner.run_backtrack(N);
            break;
        }
    }



    return true;
}
