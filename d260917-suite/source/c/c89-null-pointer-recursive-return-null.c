// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests_failed/recursive_return_null.c

#include <stdio.h>

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int *recursive_function(int depth) {
    if (depth > 0) {

        recursive_function(depth - 1);
    } else {

        return NULL;
    }
}

int main() {
    int *intPtr = recursive_function(5);

    UNSAFE_LOAD(intPtr);

    return 0;
}
