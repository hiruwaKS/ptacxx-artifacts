// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/safe_ptr_assign.c

#include <stdlib.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    int x = 6;
    int *myPtr2;
    myPtr2 = &x;
    SAFE_LOAD(myPtr2);
    *myPtr2 = 5;

    return 0;
}
