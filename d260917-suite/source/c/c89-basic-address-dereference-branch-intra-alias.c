// <svf-test-suite>@64f017e/src/basic_c_tests/branch-intra.c

int main()
{
	int *p, *q;
	int a, b, c;
	if (c) {
		p = &a;
		q = &b;
	}
	else {
		p = &b;
		q = &c;
	}

	return 0;
}
