// <svf-test-suite>@64f017e/src/basic_c_tests/funptr-simple.c

void f(int *p, int *q) {

}

void (*fptr)(int*,int*);

int main() {
	int x, y;
	int *m, *n;
	if (x) {
		m = &x, n = &x;
		fptr = f;
		fptr(m,n);
	}
	else {
		m = &x; n = &y;
		f(m,n);
	}
	return 0;
}
