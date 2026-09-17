// <svf-test-suite>@64f017e/src/basic_c_tests/ptr-dereference1.c

int main()
{
	int a,b,*c,*d;
	c = &a;
	d = &a;

	c = &b;

	return 0;
}
