// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/ExtAPI_memcpy_char_ptr.c

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

int main() {
    char* buf = (char*)malloc(10 * sizeof(char));
    char* buf_copy = (char*)malloc(10 * sizeof(char));

    memcpy(buf, "Hello", 5);
    memcpy(buf_copy, buf, 5);

    SAFE_LOAD(buf);
    SAFE_LOAD(buf_copy);

    free(buf);
    UNSAFE_LOAD(buf);

    free(buf_copy);
    UNSAFE_LOAD(buf_copy);

    return 0;
}
