// <svf-test-suite>@64f017e/src/path_tests/path2.c

int main(){

    int **p,**q;
    int *a,*b;
    int *m,*n;
    int a1,b1,m1;

    a = &a1;
    b = &b1;
    m = &m1;
	p = &a;
	q = &b;

    if(a){
	    p = &b;
	    q = &a;
    }

    *p = m;
	n = *q;

}
