// <svf-test-suite>@64f017e/src/non_annotated_tests/intra-procedure/ben3.c

#include <stdio.h>


int main(){
int a,b,*p,i,c;

if(i)
    p = &a;
else
    p = &b;

    *p = 10;

    c = *p;

    a = 5;

    b = 4;

    *p = 20;

    p = &a;

    *p = 10;

    printf("%d,%d,%d,%d\n",*p,a,b,c);

}
