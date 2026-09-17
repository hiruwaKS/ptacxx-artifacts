// <svf-test-suite>@64f017e/src/path_tests/path1.c

void foo(int**, int*);
int main(){
	int **x, *y;
	int  *c, *d,e,f;
	if(x) { x =&c; y =&e;}
	else { x= &d; y = &f;}
	foo(x,y);

}

void foo(int **p, int *q){
	*p = q;
}
