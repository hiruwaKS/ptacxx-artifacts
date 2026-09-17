// <svf-test-suite>@64f017e/src/cs_tests/cs11.c

void foo(int**a, int*b){

	*a = b;

}

int main(){

	int *p,q,*x,y;
	foo(&p,&q);

	foo(&x,&y);

	*p = 100;

}
