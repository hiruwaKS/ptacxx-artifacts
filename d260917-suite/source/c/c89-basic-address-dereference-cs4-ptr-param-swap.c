// <svf-test-suite>@64f017e/src/cs_tests/cs4.c

void foo(int **x,int**y,int **z, int *w){
	int *t;
	*y = w;
	t = *x;
	*z = t;

}

int main(){

	int *a,*b,*c,d,*p,*q,r,a1;
    a = &a1;
	foo(&a,&b,&c,&d);

	foo(&p,&p,&q,&r);

}
