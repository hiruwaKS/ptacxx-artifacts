// <svf-test-suite>@64f017e/src/path_tests/path16.c

int main(){

    int **p,*q;
    int *a,*b,c,d;
    p = &a;
    if(p){
        if(c){
            q = &c;
        }
    }
    else{
        p = &b;
        q = &d;
    }
    if(d){
        *p = q;
    }

}
