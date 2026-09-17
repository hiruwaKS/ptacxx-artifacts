// <svf-test-suite>@64f017e/src/path_tests/path11.c

void foo(int**,int* );
int main(){

    int **p,*q;
    int *a,*b,c,d;
    if(a){
        p = &a;
        q = &c;
        foo(p,q);
    }
    else{
        p = &b;
        q = &d;
        foo(p,q);
    }

    *p = q;

}

void foo(int**x,int *y){
    *x = y;
}
