// <svf-test-suite>@64f017e/src/ae_assert_tests/BASIC_array_func_3-0.c

#include "stdbool.h"

struct {
    int a;
    int b[2];
}typedef A;

int getValue(A* arr, int x) {
    return arr->b[x];
}

int main() {
    A a;
    a.a = 0;
    a.b[0] = 1;
    a.b[1] = 2;

    return 0;
}
