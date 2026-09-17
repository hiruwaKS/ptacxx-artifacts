// <svf-test-suite>@64f017e/src/mem_leak/malloc11.c

#include <stdlib.h>
int* allocation(){
	int k = 0;
	if(k<0)
		return malloc(1);
	else
		return malloc(2);

}

int main(){

	int* p = allocation();
	free(p);
}
