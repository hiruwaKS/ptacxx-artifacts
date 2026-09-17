// <svf-test-suite>@64f017e/src/fs_tests/global_2.c

int **pp, **qq;
int *p, *q;
int x, y;

void foo() {
	pp = &p;
	p = &x;
	qq = &q;
	q = &y;

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
