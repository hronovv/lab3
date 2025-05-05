#include "reverse.h"


ll reverseNumber(ll n, ll rev = 0) {
    if (n == 0) {
        return rev;
    }
    return reverseNumber(n / kTen, (rev * kTen) + (n % kTen));
}
