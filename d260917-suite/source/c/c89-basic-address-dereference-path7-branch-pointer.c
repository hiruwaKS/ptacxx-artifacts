// <svf-test-suite>@64f017e/src/path_tests/path7.c

int main(){

    int **p,*q;
    int *b,*c,d,e;

    p = &c;
    q = &e;

    if(d){
        p = &b;
    }
    else{
        q = &d;
    }

    *p = q;

}
