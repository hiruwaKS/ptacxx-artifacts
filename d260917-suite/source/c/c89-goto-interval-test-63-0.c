// <svf-test-suite>@64f017e/src/ae_assert_tests_fail/INTERVAL_test_63-0.c

#include "stdbool.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int a;

int foo(int input) {
	int output = 0;
	for(int i = 0; i < input; i++) {
		output++;
	}
	return output;
}

int main() {
    a = rand() % 8;
    int b = a;
	if(a > 0) {
		for(int i = 0; i < b; i++) {
			a = a + foo(a);
		}

	}
	while(true) {
		LOOP:
		a -= pow(2, b);
		if(a > 0) {
			goto LOOP;
		}
		exit(0);
	}
}
