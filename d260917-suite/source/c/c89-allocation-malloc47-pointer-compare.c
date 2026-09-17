// <svf-test-suite>@64f017e/src/mem_leak/malloc47.c

#include <stdio.h>


#include <stdlib.h>
int main(){

	int *p = malloc(10);
	*p = 10;
	if(p==NULL) return 0;
	printf("%d,%p",*p,(void*)p);
	free(p);
}
