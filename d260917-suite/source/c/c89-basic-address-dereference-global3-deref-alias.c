// <svf-test-suite>@64f017e/src/fs_tests/global_3.c

int **pp, **qq;
int *p, *q;
int x;

void foo() {
	*pp = &x;
}

void bar() {
	qq = &q;
	q = &x;
}

int main() {
	pp = &p;
	foo();
	bar();

	return 0;
}
