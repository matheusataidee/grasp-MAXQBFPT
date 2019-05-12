#include "solution.hpp"

Solution::Solution(int n) {
    score = 0.0;
    v = vector<int>(n, 0);
    triple_qnt = vector<int>(n, 0);
}

double Solution::getScore() {
    return score;
}