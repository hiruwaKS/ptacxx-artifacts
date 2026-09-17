// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/struct_func_ptr_2.c

#include <stdio.h>

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

struct Operations {
    void (*op_function)(int);
};

int main() {
    struct Operations *ops = NULL;
    UNSAFE_LOAD(&ops->op_function);
}
