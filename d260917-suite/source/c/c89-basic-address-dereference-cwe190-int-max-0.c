// <svf-test-suite>@64f017e/src/ae_assert_tests/cwe190_int_max-0.c

#include <string.h>
#include "stdbool.h"
#include <stdio.h>
#define ALLOCA alloca

int main() {
    int data;

    data = 0;

    data = 2;

    int result = data * 2;

}
