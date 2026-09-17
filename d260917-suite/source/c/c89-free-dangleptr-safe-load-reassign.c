// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/dangleptr_safe_load_reassign.c

#include <stdlib.h>
#include <stdbool.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    int *safePtr = (int *)malloc(sizeof(int));
    *safePtr = 777;
    SAFE_LOAD(safePtr);

    free(safePtr);

    safePtr = (int *)malloc(sizeof(int));
    *safePtr = 888;
    SAFE_LOAD(safePtr);

    return 0;
}
