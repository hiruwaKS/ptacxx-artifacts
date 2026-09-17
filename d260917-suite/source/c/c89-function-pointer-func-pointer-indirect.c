// <svf-test-suite>@64f017e/src/cs_tests/funcpoiner.c

void f(int** a, int *b)
{
 *a = b;
}

typedef void (*fp)(int**,int*);

int main()
{
        int **x,*y,*z;
        int *m,*n,m1,n1;
        m = &m1;
        n = &n1;
	fp p = &f;
	x = &y;
	(*p)(x,m);

	x = &z;
	p(x,n);

}
