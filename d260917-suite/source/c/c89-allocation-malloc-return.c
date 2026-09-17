// <svf-test-suite>@64f017e/src/fs_tests/return.c

#include <stdlib.h>

int * my_malloc(int * q) {
	int *p = malloc(*q);
	return p;
}

int main() {
	int *p, q;
	p = my_malloc(&q);
	return 0;
}
