// <svf-test-suite>@64f017e/src/basic_c_tests/field-ptr-arith-constIdx.c

struct s {
	int* f1;
	int* f2;
};

int main()
{
	int **q, **p;
	int a,b;
	struct s s1;
	s1.f1 = &a;
	s1.f2 = &b;
	q = &(s1.f1);
	p = q+1;

	return 0;
}
