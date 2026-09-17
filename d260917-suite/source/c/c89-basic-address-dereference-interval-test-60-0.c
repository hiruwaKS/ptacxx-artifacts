// <svf-test-suite>@64f017e/src/ae_assert_tests_fail/INTERVAL_test_60-0.c

#include "stdbool.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main() {
	int a;
	int b = MIN(a * a * a, a);
	if(b == a) {

	}
	else {

	}
}
