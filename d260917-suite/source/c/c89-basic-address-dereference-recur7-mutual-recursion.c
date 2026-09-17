// <svf-test-suite>@64f017e/src/cs_tests/recur7.c

int foo(int *);

static int depth = 0;

int bar(int *q){
    *q = 100;
    if(depth < 5){
        depth++;
        foo(q);
    }
}

int foo(int *a){
    *a = 10;
    if(*a!=100)
    bar(a);
}

int main(){
    int* a,b,c;
    b=0;
    a = &b;
    foo(a);
    a = &c;
    foo(a);
    return 0;
}
