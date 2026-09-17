// <svf-test-suite>@64f017e/src/mem_leak/malloc48.c

#include <stdio.h>


#include <stdlib.h>
int main() {
	int *p = malloc(1);
	printf("111");

	int a = 0;
	switch (a) {
	case 1:
		printf("111");
		break;
	case 2:
		printf("112");
		return 0;
		break;
	}
	free(p);
	return 0;
}
