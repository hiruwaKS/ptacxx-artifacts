// <svf-test-suite>@64f017e/src/path_tests/path19.c

int y,*q,*r,*f,*e,c,d;

void foo(int **p){

    if(y){
		p = &e;
		f = &y;
	}

	*p = f;

}

int main(){
	int **a,**b;
    e = 0;
	a = &q; f = &d;
	foo(a);
    b = &r; f = &c;
    foo(b);

}
