// <svf-test-suite>@64f017e/src/ae_assert_tests_fail/BASIC_array_func_1-0.c

#include "stdbool.h"
static void svf_print(int v, char *name) { (void)v; (void)name; }

int getValue(int (*arr)[2], int x, int y) {
    return arr[x][y];
}

int main() {
    int arr[2][2];
    arr[0][0] = 10;
    int v = getValue(arr, 0, 0);
    svf_print(v, "value");

    return 0;
}
