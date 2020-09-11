#include <stdio.h>
#include "pure_func.h"

int hex_to_i(int c, int cc) {
    int res = (c <= '9') ? (c - '0') : (c - 'a' + 10);
    res *= 16;
    res += (cc <= '9') ? (cc - '0') : (cc - 'a' + 10);
    return res;
}
