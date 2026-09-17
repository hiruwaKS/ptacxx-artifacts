// <svf-test-suite>@64f017e/src/cs_tests/cs9.c

int obj, t,s;
int *k =&s;
void foo(int**, int**);
int main(){
	int **x, **y;
	int *a, *b, *c, *d,*e;
    a = &t;
	x=&a; y =&b;
	foo(x,y);

	*b = 5;
	c=&t;
	c=&s;
	a=c;

	if(t) {c=&obj; x =&c; y =&e;}
	else { x= &d; y = &d;}
	e = &t;
	foo(x,y);

	*e = 10;

}

void foo(int **p, int **q){
	*p = *q;
	*q = &obj;
}
