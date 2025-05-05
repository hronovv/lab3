#include "hanoitext.h"

void HanoiText(
    int n, int i, int k,
    QTextEdit* field) {	 // i and k would be in {1,2,3} cause of 3 pins.


    if (n == 1) {
        QString info = QString("Переместим диск %1 c башни № %2 на башню № %3")
                           .arg(n)
                           .arg(i)
                           .arg(k);
        field->append(info);
    } else {
        int tmp = kSumTowerText - i - k;
        HanoiText(n - 1, i, tmp, field);
        QString info = QString("Переместим диск %1 c башни № %2 на башню № %3")
                           .arg(n)
                           .arg(i)
                           .arg(k);
        field->append(info);
        HanoiText(n - 1, tmp, k, field);
    }
}
