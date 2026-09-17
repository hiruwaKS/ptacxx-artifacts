// <svf-test-suite>@64f017e/src/basic_c_tests/struct-assignment-direct.c

struct s{
	int *a;
	int b;
};

int main()
{
	struct s s1, s2;
	struct s * p1;
	int x, y;
	s1.a = &x;
	s1.b = y;
	s2 = s1;

	return 0;
}
