// <svf-test-suite>@64f017e/src/mem_leak/malloc2.c

#include <stdio.h>


#include <stdlib.h>
void foo(int *p){

	free(p);
}

int main(){
	int *a = malloc(sizeof(int));
	int *k;
	*a = 100;
	k = a;
	printf("%d,%d,%p,%p,",*k,*a,(void*)a,(void*)k);
	foo(a);
}
