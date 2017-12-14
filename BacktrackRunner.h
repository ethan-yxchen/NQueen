#pragma once

#include "NQueenBacktrack.h"

// not finished yet, need somehow integradted to the LocalSearchTester
class BacktrackRunner{
    public:
    void run_backtrack(int NQ=20) {
        if (NQ > 104) {
            printf ("Please try sovler 0,1,2 with large N\n");
            return;
        }
        chrono::duration<double> elapse1, elapse2, elapse3;

    //    auto start1 = chrono::system_clock::now();
    //        NQueenBacktrack obj1(NQ);
    //        obj1.btRecursion(0);
            // printf("Number of Backtracking: %ld\n", obj1.numOfBk);
            // printf("Number of Nodes Generated: %ld\n", obj1.numOfNodes);
    ////        cout<<"Results: "<<(obj1.verify_conflict()?"Passed":"Failed")<<endl;
    //        auto end1 = chrono::system_clock::now();
    //        elapse1 = 1000000*(end1-start1);
    //    printf("#btRecursion() time[%*.3f] us\n\n", 11, elapse1.count());

        auto start2 = chrono::system_clock::now();
            NQueenBacktrack obj2(NQ);
            obj2.btIter();
            printf("Number of Backtracking: %ld\n", obj2.numOfBk);
            printf("Number of Nodes Generated: %ld\n", obj2.numOfNodes);
    //        cout<<"Results: "<<(obj2.verify_conflict()?"Passed":"Failed")<<endl;
            auto end2 = chrono::system_clock::now();
            elapse2 = 1000000*(end2-start2);
        printf("#btIter() time[%*.3f] us\n\n", 11, elapse2.count());

        auto start3 = chrono::system_clock::now();
            NQueenBacktrack obj3(NQ);
            obj3.fcMrv();
            printf("Number of Backtracking: %ld\n", obj3.numOfBk);
            printf("Number of Nodes Generated: %ld\n", obj3.numOfNodes);
    //        cout<<"Results: "<<(obj3.verify_conflict()?"Passed":"Failed")<<endl;
            auto end3 = chrono::system_clock::now();
            elapse3 = 1000000*(end3-start3);
        printf("#fcMrv() time[%*.3f] us\n\n", 11, elapse3.count());

    }
};