#ifndef HANOI_H
#define HANOI_H

#include <QPair>
#include <QVector>
constexpr short kSumTower = 6;


void Hanoi(int n, int i, int k, QVector<QPair<int, int>>& moves);

#endif	// HANOI_H
