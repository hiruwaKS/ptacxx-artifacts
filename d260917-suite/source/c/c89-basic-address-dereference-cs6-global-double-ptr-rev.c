// <svf-test-suite>@64f017e/src/cs_tests/cs6.c

int** g;

void foo(int **p, int *q){
	g = q;
	*p = g;
}

int main(){
	int **a,*b,*a1,b1;
	a = &a1;
	b = &b1;
	foo(a,b);

}
