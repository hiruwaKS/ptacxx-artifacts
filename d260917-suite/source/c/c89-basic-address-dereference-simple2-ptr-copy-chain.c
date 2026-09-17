// <svf-test-suite>@64f017e/src/fs_tests/simple_2.c

int main() {
	int *p, *q, *r;
	int x, y, z;
	p = &x;
	q = &y;
	r = &z;

	p = q;

	p = r;

	return 0;
}
