// <svf-test-suite>@64f017e/src/path_tests/path4.c

int main(){

    int **p,**q;
    int **x,**y;
    int *a,*b,*x1,a1,b1;
    int *m,*n,n1;

    n = &n1;
    a = &a1;
    b = &b1;
    x = y = &x1;
    p = q = &a;
    if(a){
        p = x;
        q = y;
    }

    *p = n;
    m = *q;

}
