// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests_failed/char_ptr_loop_branch_nullptr.c

#include <stdio.h>
#include <stdlib.h>

static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    char *p;
    int i = 0;
    while (i < 100) {
        if (i == 50) {
            p = NULL;
        }
        else {
            p = malloc(sizeof(char));
        }
        UNSAFE_LOAD(p);
        i++;
    }

    return 0;
}
