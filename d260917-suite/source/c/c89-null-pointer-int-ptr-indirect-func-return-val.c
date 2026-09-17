// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/int_ptr_indirect_func_return_val.c

#include <stdio.h>

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int *getNullPointer() {
    return NULL;
}

int *foo() {
    int *p = getNullPointer();
    return p;
}

int main() {
    int *ptr = foo();

    UNSAFE_LOAD(ptr);

    return 0;
}
