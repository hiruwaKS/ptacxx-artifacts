// <svf-test-suite>@64f017e/src/cs_tests/cs8.c

int obj1,obj2;
void foo(int **p, int **q){

	*p = &obj1;
	*q = &obj2;

}

int main(){

	int **a,**b,*x,*y,*z;
	if(a){
		a = &x;
		b = &y;
	}
	else{
		a = &z;
		b = &z;
	}
	foo(a,b);

}
