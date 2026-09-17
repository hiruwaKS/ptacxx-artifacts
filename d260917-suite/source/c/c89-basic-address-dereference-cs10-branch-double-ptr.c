// <svf-test-suite>@64f017e/src/cs_tests/cs10.c

int obj, t,s;
void foo(int**, int**);
int main(){
	int **x, **y;
	int *a, *b, *c, *d,*e = &obj;
	x=&a; y =&b;
	foo(x,y);

	*b = 5;
	c=&s;

	if(t) { x =&c; y =&e;}
	else { x= &d; y = &d;}
	foo(x,y);

	*e = 10;

}

void foo(int **p, int **q){
	*q = &obj;
}
