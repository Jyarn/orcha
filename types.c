#include <stdio.h>

#include "common.h"
#include "types.h"

uint64_t
to_uint(const char* str, int len)
{
    assert(len < 20);

    int r = 0;
    for (int i = 0; i < len; i++) {
        if ('0' > str[i] || str[i] > '9') break;
        r = r * 10 + str[i] - '0';
    }

    return r;
}

int64_t
to_int(const char* str, int len)
{
    assert(len < 20);
    switch (str[0]) {
        case '+':
            return to_uint(++str, len-1);
        case '-':
            return -to_uint(++str, len-1);
        default:
            return to_uint(str, len);
    }
}

float
to_float(const char* str, int len)
{
    assert(len > 0);
    uint32_t r = 0;

    // set sign bit
    r |= (str[0] == '-') << 31;

    // adjust string to account for sign
    if (str[0] == '-' || str[0] == '+') {
        str += 1;
        len -= 1;
    }

    uint64_t low, high;
    high = to_uint(str, len);

    int t = 0;
    while (str[t] == '.' || str[t] == '\0') t += 1;
    assert(t < len);

    str += t;
    len -= t;

    low = to_uint(str, len);
    unsigned int mantissa = 0;

    // parse high
    t = 0;
    while (high > 0) {
        mantissa = (mantissa >> 1) | ((high & 1) << 22);
        high >>= 1;
        t += 1;
    }

    return r;
}
