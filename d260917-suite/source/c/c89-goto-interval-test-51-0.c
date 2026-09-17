// <svf-test-suite>@64f017e/src/ae_assert_tests_fail/INTERVAL_test_51-0.c

#include <time.h>


#include "stdbool.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int digitCount(int i) {
    int counter = 0;
    LOOP:
    i = i/10;
    counter++;
    if(i != 0) {
        goto LOOP;
    }
    return counter;
}

int main() {
    srand(time(0));
	int randomNumber = rand() % 999;
    int counter = digitCount(randomNumber);

}
