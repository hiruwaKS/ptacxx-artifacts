// <svf-test-suite>@64f017e/src/cs_tests/cs18.c

int obj,b;
void bar(int **s){
    *s = &b;
}

void foo(int **p){
	*p = &obj;
	bar(p);
}
int main(){
	int **x;
	int *a, *c;
	x=&a;
	foo(x);

	x = &c;
	foo(x);

}
