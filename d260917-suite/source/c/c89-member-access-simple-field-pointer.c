// <svf-test-suite>@64f017e/src/basic_c_tests/struct-simple.c

struct s{
	int *a;
	int b;
};

int main()
{
	struct s s1, s2;
	int x, y;
	s1.a = &x;
	s2.a = s1.a;

	return 0;
}
