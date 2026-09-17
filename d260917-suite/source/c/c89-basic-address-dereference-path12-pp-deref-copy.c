// <svf-test-suite>@64f017e/src/path_tests/path12.c

int obj, t,s;
void foo(int**, int**);

int main(){
	int **x, **y;
	int *a, *b, *c, *d,*e;
	e = &t; d = &obj;
	c = &s;
	if(t) { x =&c; y =&e;}
	else { x= &d; y = &d;}
    foo(x,y);

}

void foo(int **p, int **q){
	*p = *q;
}
