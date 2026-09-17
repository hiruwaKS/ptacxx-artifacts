// <svf-test-suite>@64f017e/src/basic_c_tests/heap-indirect.c

#include <stdlib.h>
void malloc_two(int **p, int **q) {
	*p = (int*) malloc(sizeof(int));
	*q = (int*) malloc(sizeof(int));
}

int main() {
	int **o1 = malloc(100);
    int **o2 = malloc(100);
	malloc_two(o1, o2);

	return 0;
}
