// <svf-test-suite>@64f017e/src/basic_c_tests/heap-wrapper.c

#include <stdlib.h>
int * my_alloc() {
	int * p = (int *) malloc(sizeof(int));
	return p;
}

int main() {
	int * o1 = my_alloc();
	int * o2 = my_alloc();

	return 0;
}
