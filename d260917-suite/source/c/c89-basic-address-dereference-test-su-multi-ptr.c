// <svf-test-suite>@64f017e/src/fs_tests/test-su.c

int **p,**q;
int *x,*y,*z;
int a,b,c;
int main() {
	x=&a;
	y=&b;
	x=&b;
	x=&a;
	z=&b;

	return 0;
}
