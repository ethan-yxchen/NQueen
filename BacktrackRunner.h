#pragma once

#inclide "NQueenBacktrack.h"

// not finished yet, need somehow integradted to the LocalSearchTester
class BacktrackRunner: public LocalSearchRunner {
    public:
    void run(int verbose=0) {
        NQueenBacktrack obj(25);
        obj.fcMrv();
        cout<<"Number of Backtracking: "<<obj.getNumOfBk()<<endl;
        cout<<"Results: "<<(obj.verify_conflict()?"Passed":"Failed")<<endl;
    }

    void dump_bins() const {
        // no bin_diag, bin_anti_diag
    }
};