// <svf-test-suite>@64f017e/src/ae_assert_tests_fail/INTERVAL_test_39-0.c

#include "stdbool.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count = 0;

int fib(int i) {
    count++;
    if(i == 0) {
        return 0;
    }
    if(i == 1) {
        return 1;
    }
    return fib(i - 1) + fib(i - 2);
}

int main() {
    int i = 3;
    if(i >= 0) {
        fib(i);

    }
}
