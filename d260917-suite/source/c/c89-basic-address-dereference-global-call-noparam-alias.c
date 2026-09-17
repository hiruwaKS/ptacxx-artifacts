// <svf-test-suite>@64f017e/src/basic_c_tests/global-call-noparam.c

#include <stdlib.h>


int *p = NULL;
int *q = NULL;
int c;

void foo() {

}

void bar() {
	q = &c;
}

int main() {
	int a, b;
	p = &a;
	q = p;
	p = &c;
}
