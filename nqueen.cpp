#include "NQueenSwapSolver.h"
#include "LocalSearchRunner.h"
#include "LocalSearchTester.h"

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

    LocalSearchTester<LocalSearchRunner<NQueenSwapSolver>> tester(N, repeat, 
            soft_threshold, prob_plateau);
    
    tester.test(verbose);
    tester.stats();
    
    return true;
}
