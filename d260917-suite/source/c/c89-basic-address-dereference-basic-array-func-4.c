// <svf-test-suite>@64f017e/src/ae_assert_tests/BASIC_array_func_4-0.c

#include "stdbool.h"

int getValue(int* arr, int x) {
    return arr[x];
}

int main() {
    int arr[2];
    arr[0] = 0;
    arr[1] = 1;
    int res = getValue(arr, 1);

    return 0;
}
