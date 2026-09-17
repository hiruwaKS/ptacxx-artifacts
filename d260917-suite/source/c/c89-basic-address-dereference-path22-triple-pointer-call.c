// <svf-test-suite>@64f017e/src/path_tests/path22.c

void foo(int ***,int**);
int obj;
int main(){

    int ***p,**q, **a, **b, *c, *m,*n,d;
    m = &d;
    a = b = &c;
    if(a){
        p = &a;
        q = &c;
        foo(p,q);
    }
    else{
        p = &b;
        q = &c;
        foo(p,q);
    }

   *a = m;
   n = *b;

}

void foo(int ***x,int **y){
    *x = y;
}
