// <svf-test-suite>@64f017e/src/cs_tests/recur8.c

#include <stdlib.h>
int z1,z2;
void foo(int **p);
void bar(int **a){
	if(z1>5) return;
	z1++;
	int *c, b;
	*a = &b;
	c = *a;

	foo(a);
}

void foo(int** p){

	p = malloc(10);
	*p = &z2;
	bar(p);
}

int main(){

	int **x, *y;
	x = &y;
	y = &z1;
	foo(x);
}
