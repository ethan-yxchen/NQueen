#include <cassert>

#include "NQueenSwapSolver.h"
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
    const char *out = (argc > arg)? argv[arg] : nullptr;
    arg++;

    LocalSearchTester<LocalSearchRunner<RandomGreedySolver>> tester(N, repeat, 
            soft_threshold, prob_plateau);
    
    tester.test(verbose, out);
    tester.stats();
    
    return true;
}
