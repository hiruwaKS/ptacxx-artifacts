// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/int_ptr_func_return_val.c

#include <stdio.h>

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int* getNullPointer() {
    return NULL;
}

int main() {
    int *ptr = getNullPointer();

    UNSAFE_LOAD(ptr);

    return 0;
}
