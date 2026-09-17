// <svf-test-suite>@64f017e/src/path_tests/path15.c

int main(){
    int **p, *q, **w,*v, *a,a1,q1;
    a = &a1;
    p = &a;
    q = &q1;
    w = &a;
    if(p)
        *p = q;
    else
        w = &a;

    v = *w;

}
