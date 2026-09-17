// <svf-test-suite>@64f017e/src/basic_c_tests/global-nested-calls.c

int **pp, **qq;
int *p, *q;
int x;

void foo() {
	pp = &p;
	p = &x;
}

void bar() {
	qq = &q;
	q = &x;
}

int main() {

	foo();
	bar();
	return 0;
}
