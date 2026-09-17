// <svf-test-suite>@64f017e/src/cs_tests/cs15.c

void foo(int **w,int**x,int **y, int *z){
	int *t;
	*y = z;
	t = *x;
	*w = t;

}

void bar(int **p1,int**p2,int **p3, int *p4){
	foo(p1,p2,p3,p4);
}

int main(){

	int **a,**b,**c,*d,*a1,*b1,*c1,d1;
	a = &a1;
	b = &b1;
	c = &b1;
	d = &d1;
	bar(a,b,c,d);

}
