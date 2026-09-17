// <svf-test-suite>@64f017e/src/mem_leak/malloc13.c

#include <stdio.h>


#include <stdlib.h>
int* a[100];
int main(){

	int i = 0;
	a[i] = malloc(10);
	printf("%p",(void*)a[i]);
	free(a[i]);
	return 0;
}
