// <svf-test-suite>@64f017e/src/path_tests/path10.c

void foo(int** s);
void bar(int** s);
int k;
int main(){

    int **p,*q;
    int *b,*c,e;
    if(e){
        p = &b;
        foo(&q);
    }
    else{
        p = &c;
        q = &e;
    }

    *p = q;

}

void foo(int**x){
    bar(x);
}

void bar(int**s){
    *s = &k;
}
