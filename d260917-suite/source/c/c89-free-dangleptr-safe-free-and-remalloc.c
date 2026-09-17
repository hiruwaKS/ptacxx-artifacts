// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/dangleptr_safe_free_and_remalloc.c

#include <stdlib.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    int *myPtr = (int*)malloc(sizeof(int));
    free(myPtr);
    UNSAFE_LOAD(myPtr);
    myPtr = (int*)malloc(sizeof(int));
    *myPtr = 200;
    SAFE_LOAD(myPtr);
    return 0;
}
