// <svf-test-suite>@64f017e/src/path_tests/path14.c

int main(){
    int **p,*q;
    int *a,*b,c,d,e;
    q = &c;
    if(a){
        p = &a;
        if(c){
            q = &d;
        }
    }
    else{
        p = &b;
        q = &e;
    }

    *p = q;

}
