// <svf-test-suite>@64f017e/src/fs_tests/function_pointer.c

void func1(int *p, int *q) {

	*p = *q;
}

void (*fp)(int*,int*);

int main() {
	int x, y;
	int *m, *n;
	if (x) {
		m = &x, n = &x;
		fp = func1;
		fp(m,n);
	}
	else {
		m = &x; n = &y;

	}
	return 0;
}
