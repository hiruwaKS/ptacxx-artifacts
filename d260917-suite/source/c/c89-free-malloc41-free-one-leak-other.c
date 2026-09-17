// <svf-test-suite>@64f017e/src/mem_leak/malloc41.c

#include <stdio.h>


#include <stdlib.h>
int* bar1(int* b){
	  return b;
	    }

void foo(int *x,int *y){

	    int*k=bar1(x);
		    free(k);

			    int* t = bar1(y);
				    printf("%p",(void*)t);
}

void tmp(){

	  int* p = malloc(10);
	    int* q = malloc(10);
		  foo(p,q);

}

int main(){

	  tmp();
}
