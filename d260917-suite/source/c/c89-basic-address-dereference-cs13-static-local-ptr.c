// <svf-test-suite>@64f017e/src/cs_tests/cs13.c

#include <stdio.h>


void foo(int*);
int ss = 20;
int main(){
    int *a,*b,obj,t;
    a=&obj;
    foo(a);
    *a=200;
    b=&t;
    foo(b);

}

void foo(int* x){
     static int* k =&ss;
    printf("%d\n", *k);
    *k=200;
    k=x;
     *x= 100;
}
