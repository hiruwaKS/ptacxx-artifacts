// <svf-test-suite>@64f017e/src/basic_c_tests/CI-local.c

void foo(int *m, int *n)
{

}

int main()
{
	int *p, *q;
	int a,b;
	if (a) {
		p = &a;
		q = &b;
		foo(p,q);
	}
	else {
		p = &b;
		q = &a;
		foo(p,q);
	}
	return 0;
}
