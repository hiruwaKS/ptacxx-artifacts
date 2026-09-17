// <svf-test-suite>@64f017e/src/ae_assert_tests/wto_assert_04.c

 #include <stdlib.h>
 #include "stdbool.h"
 #include "math.h"

static void svf_print(int v, char *name) { (void)v; (void)name; }

int main() {
    int a = rand();
    int result = 0;

    if (a > 0 && a < 2) {

        result = 100;

    }
    else if (a > 4 && a < 6) {

        result = 200;

    }
    else if (a > 9 && a < 11) {

        result = 300;

    }
    else {

        int b = rand();

        result = -1;
    }

    return 0;
}
