#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <bits/stdc++.h>

using namespace std;

extern vector<vector<double> > weights;
extern vector<vector<int> > reversed_triples;

class Solution {
    private:
        double score;
        int len;
        vector<int> v;
        vector<int> triple_qnt;
    public:
        Solution(int n);

        double getScore();

        void add(int p);

        void sub(int p);

        bool hasElem(int p);
        
        bool canAdd(int p);

        bool canPerm(int in, int out);

        bool localSearch();
};

#endif /* _SOLUTION_H_ */