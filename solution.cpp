#include "solution.hpp"

Solution::Solution(int n) {
    len = n;
    score = 0.0;
    v = vector<int>(n, 0);
    triple_qnt = vector<int>(n, 0);
}

double Solution::getScore() {
    return score;
}

void Solution::add(int p) {
    if (v[p] == 1) return;
    double diff = 0.0;
    for (int i = 0; i < len; i++) {
        if (i == p) {
            diff += weights[p][p];
        } else {
            diff += (weights[i][p] + weights[p][i]) * v[i] ;
        }
    }
    v[p] = 1;
    score += diff;
    for (int i = 0; i < reversed_triples[p].size(); i++) {
        int val = reversed_triples[p][i];
        triple_qnt[val]++;
    }
}

void Solution::sub(int p) {
    if (v[p] == 0) return;
    double diff = 0.0;
    for (int i = 0; i < len; i++) {
        if (i == p) {
            diff += weights[p][p];
        } else {
            diff += (weights[i][p] + weights[p][i]) * v[i] ;
        }
    }
    v[p] = 0;
    score -= diff;
    for (int i = 0; i < reversed_triples[p].size(); i++) {
        int val = reversed_triples[p][i];
        triple_qnt[val]--;
    }
}

bool Solution::hasElem(int p) {
    if (v[p] == 1) return true;
    return false;
}

bool Solution::canAdd(int p) {
    for (int i = 0; i < reversed_triples[p].size(); i++) {
        int val = reversed_triples[p][i];
        if (triple_qnt[val] == 2) return false;
    }
    return true;
}

bool Solution::canPerm(int in, int out) {
    set<int> rev;
    for (int i = 0; i < reversed_triples[in].size(); i++) {
        int val = reversed_triples[in][i];
        rev.insert(val);
    }
    for (int i = 0; i < reversed_triples[out].size(); i++) {
        int val = reversed_triples[out][i];
        if (rev.find(val) != rev.end()) {
            rev.erase(val);
        }
    }
    for (set<int>::iterator it = rev.begin(); it != rev.end(); it++) {
        int val = *it;
        if (triple_qnt[val] == 2) return false;
    }
    return true;
}

bool Solution::localSearch() {
    double current_score = score;
    for (int i = 0; i < len; i++) {
        if (!v[i]) continue;
        sub(i);
        if (score > current_score) {
            return true;
        } else {
            add(i);
        }
    }

    for (int i = 0; i < len; i++) {
        if (v[i]) continue;
        if (!canAdd(i)) continue;
        add(i);
        if (score > current_score) {
            return true;
        } else {
            sub(i);
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (i == j) continue;
            if (!v[i] && v[j]) {
                if (!canPerm(i, j)) continue;
                add(i);
                sub(j);
                if (score > current_score) {
                    return true;
                } else {
                    sub(i);
                    add(j);
                }
            }
        }
    }
    return false;
}