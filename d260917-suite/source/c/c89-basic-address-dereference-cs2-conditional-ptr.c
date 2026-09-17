// <svf-test-suite>@64f017e/src/cs_tests/cs2.c

int obj;
void foo(int **p, int **q, int **r){

	*r = *p;
	*q = &obj;

}

int main(){

	int **a,**b,**c,**d,**e,**f,*x,*y,*z,*w,*k,x1,y1,z1,w1,k1;
	x = &x1;
	y = &y1;
	z = &z1;
	w = &w1;
	k = &k1;

	a = &x;
	b = &y;
	c = &z;
	if(a){

		d = &w;
		e = &w;
		f = &k;
	}
	foo(a,b,c);

	foo(d,e,f);

}
