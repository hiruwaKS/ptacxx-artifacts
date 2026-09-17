// <svf-test-suite>@64f017e/src/fs_tests/simple_3.c

int main() {
	int **p, **q;
	int *x, *y;
	int x0, y0;
	p = &x;
	q = &y;
	*p = &x0;
	*q = &y0;

	*p = *q;

	return 0;
}
