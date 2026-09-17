// <svf-test-suite>@64f017e/src/ae_assert_tests_fail/INTERVAL_test_25-0.c

#include <time.h>


#include "stdbool.h"
static void svf_print(int v, char *name) { (void)v; (void)name; }
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int foo() {
    int i = 0;
    bool a = true;
    do {
        i++;
    } while(i < 5 && a);
    return i;
}

int bar() {
    int i = 0;
    bool a = false;
    do {
        i++;
    } while(i < 5 && a);
    return i;
}

int main() {
	srand(time(0));
	int a = rand() % 2;
    int b = (a) ? foo() : bar();
    if(a) {

    }
    else {

    }
}
