// <svf-test-suite>@64f017e/src/cs_tests/cs17.c

void bar(int**k, int**s){

	*k = *s;

}

void foo(int**x,int**y,int**z){
	int t;
	*y = &t;
	*z = *x;
}

int main(){
	int *p1,*q1,*r1,*a1,*b1,*c1,q2,a2;
	int **p = &p1;
	int **q = &q1;
    q1 = &q2;
	int **r = &r1;
	int **a = &a1;
    a1 = &a2;
	int **b = &b1;
	int **c = &c1;
	bar(&p,&q);

	foo(p,q,r);

	foo(a,b,c);

}
