// <svf-test-suite>@64f017e/src/fs_tests/branch_1.c

int main() {
	int *p, *q;
	int x, y;
	if (x)
		p = &x;
	else
		p = &y;
	q = &y;

	return 0;
}
