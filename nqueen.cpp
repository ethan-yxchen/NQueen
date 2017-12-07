#include "NQueenSwapSolver.h"
#include "LocalSearchRunner.h"
#include "LocalSearchTester.h"

int main(int argc, const char *argv[]) {
    int N = (argc > 1)? stoi(string(argv[1])) : 4;
    int repeat = (argc > 2)? stoi(string(argv[2])) : 1;
    int soft_threshold = (argc > 3)? stoi(string(argv[3])) : 2;
    int prob_plateau = (argc > 4)? stoi(string(argv[4])) : 3;
    int verbose = (argc > 5)? stoi(string(argv[5])) : 0;

    LocalSearchTester<LocalSearchRunner<NQueenSwapSolver>> tester(N, repeat, 
            soft_threshold, prob_plateau);
    
    tester.test(verbose);
    tester.stats();
    
    return true;
}
