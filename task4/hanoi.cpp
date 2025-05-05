#include "hanoi.h"


void Hanoi(int n, int i, int k, QVector<QPair<int, int>>& moves) {
    if (n == 1) {
        moves.append(qMakePair(i, k));
    } else {
        int tmp = kSumTower - i - k;
        Hanoi(n - 1, i, tmp, moves);
        moves.append(qMakePair(i, k));
        Hanoi(n - 1, tmp, k, moves);
    }
}
