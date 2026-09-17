// <svf-test-suite>@64f017e/src/fs_tests/function_pointer_2.c

void func1(int **p, int **q) {
	*p = *q;

}

void (*fp)(int**,int**);

int main() {
	int o1, o2;
	int *x, *y;
	int **m, **n;
	x = &o1;
	y = &o2;
	m = &x;
	n = &x;
	fp = func1;
	fp(m,n);

	return 0;
}
