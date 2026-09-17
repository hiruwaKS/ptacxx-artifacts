// <svf-test-suite>@64f017e/src/cs_tests/cs14.c

void foo(int*,int*);
int main(){
	int*x, *y;
	int a,b, c;
	if(c)x=&a;
	else x=&b;

	foo(x,y);
	x = &c;
	foo(x,y);

}

void foo(int *p,int*q){
	*p = 100;
}
