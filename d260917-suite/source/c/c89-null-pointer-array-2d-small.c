// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/array_2d_small.c

#include <stdio.h>

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    int *arr[2][2];
    arr[0][0] = NULL;
    arr[0][1] = NULL;
    arr[1][0] = NULL;
    arr[1][1] = NULL;

    UNSAFE_LOAD(arr[0][0]);
    UNSAFE_LOAD(arr[0][1]);
    UNSAFE_LOAD(arr[1][0]);
    UNSAFE_LOAD(arr[1][1]);
}
