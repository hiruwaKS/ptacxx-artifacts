// <svf-test-suite>@64f017e/src/ae_assert_tests/BASIC_array_struct_0-0.c

#include "stdbool.h"

struct {
    int a;
    int b;
}typedef A;
int main() {
    A a[2];
    a[0].a = 10;
    a[0].b = 11;
    a[1].a = 20;
    a[1].b = 21;
    int c = 0;

    return 0;
}
