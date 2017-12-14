#pragma once

#inclide "NQueenBacktrack.h"

// not finished yet, need somehow integradted to the LocalSearchTester
class BacktrackRunner: public LocalSearchRunner {
    public:
    void run(int verbose=0) {
        chrono::duration<double> elapse1, elapse2, elapse3;
        const int NQ = 30;

    //    auto start1 = chrono::system_clock::now();
    //        NQueenBacktrack obj1(NQ);
    //        obj1.btRecursion(0);
    //        cout<<"Number of Backtracking: "<<obj1.numOfBk<<endl;
    //        cout<<"Number of Nodes Generated: "<<obj1.numOfNodes<<endl;
    ////        cout<<"Results: "<<(obj1.verify_conflict()?"Passed":"Failed")<<endl;
    //        auto end1 = chrono::system_clock::now();
    //        elapse1 = 1000000*(end1-start1);
    //    printf("#btRecursion() time[%*.3f] us\n\n", 11, elapse1.count());

        auto start2 = chrono::system_clock::now();
            NQueenBacktrack obj2(NQ);
            obj2.btIter();
            cout<<"Number of Backtracking: "<<obj2.numOfBk<<endl;
            cout<<"Number of Nodes Generated: "<<obj2.numOfNodes<<endl;
    //        cout<<"Results: "<<(obj2.verify_conflict()?"Passed":"Failed")<<endl;
            auto end2 = chrono::system_clock::now();
            elapse2 = 1000000*(end2-start2);
        printf("#btIter() time[%*.3f] us\n\n", 11, elapse2.count());

        auto start3 = chrono::system_clock::now();
            NQueenBacktrack obj3(NQ);
            obj3.fcMrv();
            cout<<"Number of Backtracking: "<<obj3.numOfBk<<endl;
            cout<<"Number of Nodes Generated: "<<obj3.numOfNodes<<endl;
    //        cout<<"Results: "<<(obj3.verify_conflict()?"Passed":"Failed")<<endl;
            auto end3 = chrono::system_clock::now();
            elapse3 = 1000000*(end3-start3);
        printf("#fcMrv() time[%*.3f] us\n\n", 11, elapse3.count());

    //        obj.printASolution();

        return 0;
    }

    void dump_bins() const {
        // no bin_diag, bin_anti_diag
    }
};