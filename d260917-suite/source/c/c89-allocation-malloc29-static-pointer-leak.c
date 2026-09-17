// <svf-test-suite>@64f017e/src/mem_leak/malloc29.c

#include <stdio.h>


#include <stdlib.h>
int func(){
	static int* q;
	int *p = malloc(10);
	q = p;
	printf("%p%p",(void*)p,(void*)q);

}

int main(){
	func();
}
