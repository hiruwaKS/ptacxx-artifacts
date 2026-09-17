// <svf-test-suite>@64f017e/src/mem_leak/malloc15.c

#include <stdlib.h>
int *foo(){

	return malloc(1);

}

int main(){

int *p = foo();
free(p);
return 0;
}
