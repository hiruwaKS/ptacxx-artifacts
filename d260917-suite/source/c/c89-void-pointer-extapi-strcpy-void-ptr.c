// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/ExtAPI_strcpy_void_ptr.c

#include <string.h>
#include <stdlib.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    void* p = malloc(20);
    void* p_copy = malloc(20);

    strcpy((char*)p, "Hello");
    strcpy((char*)p_copy, "World");

    strcpy((char*)p, (char*)p_copy);
    strcpy((char*)p_copy, (char*)p);

    SAFE_LOAD(p);
    SAFE_LOAD(p_copy);

    free(p);
    UNSAFE_LOAD(p);

    free(p_copy);
    UNSAFE_LOAD(p_copy);

    return 0;
}
