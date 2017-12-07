#pragma once

#include <vector>
#include <cstdio>
#include <valarray>
#include <cmath>
#include <string>

#include "Tester.h"

using namespace std;


template <class LocalSearchRunner>
class LocalSearchTester {

public:
    int NQ;
    double NLog;
    vector<uint64_t> steps, attempts;
    vector<double> elapse;
    vector<int> conflicts;
    int repeat;
    int soft_threshold;
    int prob_plateau;

    LocalSearchTester(int NQ, int repeat, int soft_threshold, int prob_plateau)
      : NQ(NQ), NLog(NQ * log(NQ)), repeat(repeat),
        soft_threshold(soft_threshold), prob_plateau(prob_plateau)
        {}
    
    void show_config() const {
        printf("repeat[%*d]  ", 5, repeat);
        printf("soft_threshold[%*d]  ", 3, soft_threshold);
        printf("prob_plateau[%*d]  ", 3, prob_plateau);
        printf("\n");
    }
    
    template <typename T>
    void stats(string name, vector<T> vec) const {
        auto _ = mean_std(vec);
        double mu = _.first, std = _.second;
        
        printf("%*s %.2f (%.2f %.2f%%)   ",
            10, name.c_str(), mu, std, std/mu*100);
        printf("1/N %.2f (%.2f)   ", mu/NQ, std/NQ);
        printf("1/Nlog(N) %.2f (%.2f)\n", mu/NLog, std/NLog);
    }
    
    void stats() const {
        stats("steps", steps);
        stats("attempts", attempts);
        stats("elapse", elapse);
        int f = 0;
        for (int i: conflicts)
            if (i != 0)
                f++;
        printf("#fail: %d\n", f);
    }
    
    void test(bool verbose=false) {
        for (int i=0; i<repeat; ++i) {
            LocalSearchRunner runner(NQ);
            runner.solver.soft_threshold = soft_threshold;
            runner.solver.prob_plateau = prob_plateau;
            runner.run(verbose);
            steps.push_back(runner.steps);
            attempts.push_back(runner.attempts);
            elapse.push_back(runner.elapse.count());
            conflicts.push_back(runner.solver.conflicts);
            if (verbose)
                runner.stats();
        }
    }
};
