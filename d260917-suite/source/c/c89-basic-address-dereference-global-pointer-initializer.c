// <svf-test-suite>@64f017e/src/basic_c_tests/global-initializer.c

int x;
int *p, *q;
int **pp = &p;
int **qq = &q;

void foo() {
	p = &x;
}

void bar() {
	q = &x;
}

int main() {

	foo();
	bar();
	return 0;
}
