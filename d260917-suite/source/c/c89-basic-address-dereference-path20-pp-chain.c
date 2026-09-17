// <svf-test-suite>@64f017e/src/path_tests/path20.c

int main(){

    int**a,**b, *f,*g,r,w,q,*obj,k;
    a = &f;
    b = &f;
    f = &k;
    if(a){
        a = &f;
        f = &r;
    }
    else{
        a = &g;
        g = &w;
    }
    a = b;

    *a = &q;
    obj = *b;

}
