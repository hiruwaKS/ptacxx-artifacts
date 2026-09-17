// <svf-test-suite>@64f017e/src/fs_tests/global_5.c

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
