// <svf-test-suite>@64f017e/src/cs_tests/cs16.c

#include <stdlib.h>
int *alloc( int size){

	return malloc(1);

}

void foo(int **p){

	*p = alloc(1);

}

int main(){

	int *a,*b,*c;
	foo(&a);
	foo(&b);
	foo(&c);

}
