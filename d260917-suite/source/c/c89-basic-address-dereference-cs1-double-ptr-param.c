// <svf-test-suite>@64f017e/src/cs_tests/cs1.c

void foo(int **x, int **y){

	x = y;
}

int main(){

	int *a, *b;
	int a1, b1;
	a = &a1;
	b = &b1;
	foo(a,b);

}
