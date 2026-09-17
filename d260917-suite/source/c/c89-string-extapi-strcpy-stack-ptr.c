// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/ExtAPI_strcpy_stack_ptr.c

#include <string.h>
#include <stdlib.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    char c;
    char* p = &c;
    char* p_copy = (char*)malloc(sizeof(char));

    strcpy(p_copy, "A");
    strcpy(p_copy, "B");

    SAFE_LOAD(p);
    SAFE_LOAD(p_copy);

    free(p_copy);
    UNSAFE_LOAD(p_copy);

    return 0;
}
