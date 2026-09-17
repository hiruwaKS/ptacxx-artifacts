// <svf-test-suite>@64f017e/src/path_tests/path18.c

int x,y,*q,*f,*e,d;

void foo(int **p){
	f = &x;
	if(x){
		p = &e;
		f = &y;
	}

	*p = f;

}

int main(){
	int **a,c;
	a = &q; f = &d;
	foo(a);
}
