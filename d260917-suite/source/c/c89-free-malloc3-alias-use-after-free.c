// <svf-test-suite>@64f017e/src/mem_leak/malloc3.c

#include <stdio.h>


#include <stdlib.h>
int* foo(int *p){

	return p;
}

void bar(int *s){
	free(s);
}
int main(){
	int *k;
	int *a = malloc(sizeof(int));
	k = foo(a);
	*a = 100;
	printf("%d,%d,%p,%p,",*k,*a,(void*)a,(void*)k);
	bar(k);
}
