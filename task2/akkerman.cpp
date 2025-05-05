#include "akkerman.h"


ull Akerman(ull m, ull n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return Akerman(m - 1, 1);
    } else {
        return Akerman(m - 1, Akerman(m, n - 1));
    }
}
