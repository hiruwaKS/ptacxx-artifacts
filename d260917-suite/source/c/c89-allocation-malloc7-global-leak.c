// <svf-test-suite>@64f017e/src/mem_leak/malloc7.c

#include <stdio.h>


#include <stdlib.h>
int *g;
int main(){

	int *p = malloc(1);
	g = p;
	printf("%p,%p",(void*)g,(void*)p);
	free(g);
	return 0;
}
