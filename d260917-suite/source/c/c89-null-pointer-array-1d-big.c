// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests_failed/array_1d_big.c

#include <stdio.h>
#include <stdlib.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

#define SIZE 100

int main() {
    int *arr[SIZE];
    int i;

    for (i = 0; i < SIZE; i++) {
            if (i < SIZE / 2) {
                arr[i] = NULL;
            } else {
                arr[i] = malloc(sizeof(int));
                *arr[i] = 1024;
            }
    }

    for (i = 0; i < SIZE; i++) {
        if (i < SIZE / 2)
            UNSAFE_LOAD(arr[i]);
        else
            SAFE_LOAD(arr[i]);
    }

    return 0;
}
