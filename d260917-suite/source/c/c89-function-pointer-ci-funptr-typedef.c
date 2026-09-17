// <svf-test-suite>@64f017e/src/basic_c_tests/CI-funptr.c

void f(int *m, int *n)
{

}

typedef void (*fp)(int*m, int*n);

int main()
{
	int a,b,c,d;
	int *pa, *pb;
    fp p;
	pa = &a, pb = &b;
	f(pa, pb);
    p = f;
	pb = &a;
    (*p)(pa, pb);
	return 0;
}
