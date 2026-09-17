// <svf-test-suite>@64f017e/src/ae_assert_tests/BASIC_bi_add_2-0.c

#include "stdbool.h"
static void set_value(int v, int lo, int hi) { (void)v; (void)lo; (void)hi; }
static void svf_print(int v, char *name) { (void)v; (void)name; }
int main() {
    volatile int i;
    set_value(i, 0, 100);
    volatile int a, c;
    a = i + 1;
    c = a;

    return 0;
}
