#include <stdio.h>

#include "common.h"
#include "types.h"

void* __temp__;

// Define an enviroment to conduct the test in
#define TEST_ENV(body) { body }

// Create a duplicate of a variable for the current enviroment
#define TEST_IMPORT(type, variable) \
    __temp__ = &variable; \
    type variable = *(type*)__temp__;

// Create a test block
#define TEST_BLOCK(name, body) { \
    int nfailed = 0; \
    printf("\n--+ %s +--\n", #name); \
    body \
    if (nfailed != 0) \
        printf("%s: %d tests failed!\n", #name, nfailed); \
    else \
        printf("%s: all tests passed!\n", #name); \
}

// Test for equality
#define TEST_EQ(a, b) { \
    if (a != b) { \
        printf("(F) %s != %s\n", #a, #b); \
        nfailed += 1; \
    } \
}


int
main(void)
{
    TEST_BLOCK(Types,
            TEST_EQ(sizeof(int64_t), 8);
            TEST_EQ(sizeof(uint64_t), 8);
            TEST_EQ(sizeof(float), 4);
            TEST_EQ(sizeof(double), 8);
            TEST_EQ(to_uint("1882", 4), 1882);
            TEST_EQ(to_uint("1982", 0), 0);
            TEST_EQ(to_uint("192381", 2), 19);
            TEST_EQ(to_uint("234", 10), 234);
            TEST_EQ(to_int("1882", 4), 1882);
            TEST_EQ(to_int("-1882", 5), -1882);
            TEST_EQ(to_int("+1882", 5), 1882);
    );

    TEST_BLOCK(Test Block,
        int a = 0;
        int b = 0;

        TEST_ENV(
            TEST_EQ(a, 0);
            TEST_IMPORT(int, a);
            TEST_IMPORT(int, b);

            a = 1000;

            TEST_EQ(b, 0);
            b = 500;

            TEST_EQ(a, 1000);
            TEST_EQ(b, 500);
        );

        TEST_EQ(a, 0);
        TEST_EQ(b, 0);
    );
}
