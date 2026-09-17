// <svf-test-suite>@64f017e/src/ae_assert_tests/INTERVAL_test_16-0.c

#include "stdbool.h"
#include "math.h"
static void svf_print(int v, char *name) { (void)v; (void)name; }
static void set_value(int v, int lo, int hi) { (void)v; (void)lo; (void)hi; }

void foo(int* i) {
    *i = *i + 1;
    if(*i < 10) {
        foo(i);
    }
}

int main() {
    int i;
    set_value(i, 0, 5);
    foo(&i);

}
