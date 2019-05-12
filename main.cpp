#include <bits/stdc++.h>

#include "solution.hpp"


using namespace std;

int n;
double alpha = 0.2;
vector<vector<double> > weights;
vector<vector<int> > triples;
vector<vector<int> > reversed_triples;
vector<pair<double, int> > candidates;
vector<pair<double, int> > rcl;

int lFunction(int u, int pi_1, int pi_2) {
    return 1 + (pi_1 * u + pi_2) % n;
}

void mountTriples() {
    for (int i = 0; i < n; i++) {
        triples[i][0] = i + 1;

        int g = lFunction(i, 131, 1031);
        if (g != triples[i][0]) {
            triples[i][1] = g;
        } else {
            triples[i][1] = 1 + (g % n);
        }

        int h = lFunction(i, 193, 1093);
        int x = 1 + (h % n);
        if (h != triples[i][0] && h != triples[i][1]) {
            triples[i][2] = h;
        } else if (x != triples[i][0] && x != triples[i][1]) {
            triples[i][2] = x;
        } else {
            triples[i][2] = 1 + (h + 1) % n;
        }
        sort(triples[i].begin(), triples[i].end());
        for (int j = 0; j < 3; j++) {
            triples[i][j]--;
            reversed_triples[triples[i][j]].push_back(i);
        }
    }
}

bool contructionIteration(Solution& cur) {
    rcl.clear();
    for (int i = 0; i < n; i++) {
        if (!cur.hasElem(i) && cur.canAdd(i)) {
            rcl.push_back(candidates[i]);
        }
    }    
    if (rcl.size() < 1) return false;
    sort(rcl.begin(), rcl.end());
    for (int i = 0; i < rcl.size() / 2; i++) {
        swap(rcl[i], rcl[rcl.size() - 1 - i]);
    }

    double maxi = rcl[0].first;
    double mini = rcl[rcl.size() - 1].first;
    if (maxi < 0) return false;
    double acceptable = maxi - (maxi - mini) * alpha;
    int qnt;
    for (qnt = 0; qnt < n && rcl[qnt].first >= acceptable; qnt++);
    int lucky = rand() % qnt;
    int id = rcl[lucky].second;
    for (int i = 0; i < n; i++) {
        candidates[i].first += weights[i][id] + weights[id][i];
    }
    cur.add(id);
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "No instance provided" << endl;
        return -1;
    }
    ifstream fin(argv[1]);
    fin >> n;
    weights = vector<vector<double> >(n, vector<double>(n, 0.0 ));
    triples = vector<vector<int> >(n, vector<int>(3, 0));
    reversed_triples = vector<vector<int> >(n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            fin >> weights[i][j];
            if (j > i) {
                weights[j][i] = 0;
            }
        }
    }
    fin.close();
    mountTriples();

    // GRASP main loop
    srand(0);
    Solution best_solution(n);
    for (int z = 0; z < 500; z++) {
        Solution cur(n);
        candidates.clear();
        for (int i = 0; i < n; i++) {
            candidates.push_back({weights[i][i], i});
        }
        while (contructionIteration(cur));
        cout << "z = " << z << " solution score = " << cur.getScore() << endl;
        if (cur.getScore() > best_solution.getScore()) {
            best_solution = cur;
        }
    }
    cout << best_solution.getScore() << endl;
    /*Solution solution(n);
    Solution a(5);
    cout << solution.getScore() << endl;
    int adders[9] = {2, 3, 4, 9, 11, 14, 15, 16, 19};
    for (int i = 0; i < 9; i++) {
        solution.add(adders[i]);
    }
    cout << solution.getScore() << endl;
    a = solution;
    cout << a.getScore() << endl;*/

    return 0;
}