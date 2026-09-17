// <svf-test-suite>@64f017e/src/fs_tests/simple_1.c

int main() {
	int *p, *q;
	int x, y;
	p = &x;
	q = &y;

	p = q;

	return 0;
}
