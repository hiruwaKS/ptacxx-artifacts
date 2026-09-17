// <svf-test-suite>@64f017e/src/ae_nullptr_deref_tests/array_of_struct.c

#include <stdlib.h>

static void SAFE_LOAD(void *ptr) { (void)ptr; }
static void UNSAFE_LOAD(void *ptr) { (void)ptr; }

struct S {
    int *intPtr;
};

int main() {
    struct S arrStruct[3];

    arrStruct[0].intPtr = malloc(sizeof(int));
    *arrStruct[0].intPtr = 1024;

    arrStruct[1].intPtr = NULL;

    SAFE_LOAD(arrStruct[0].intPtr);
    UNSAFE_LOAD(arrStruct[1].intPtr);
    UNSAFE_LOAD(arrStruct[2].intPtr);

    return 0;
}
