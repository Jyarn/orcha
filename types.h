#ifndef __TYPES__H
#define __TYPES__H

#include <stdint.h>

typedef struct {
    uint64_t len;
    const char* val;
} str_t;

uint64_t to_uint(const char*, int);
int64_t to_int(const char*, int);
float to_float(const char*, int);

#endif
