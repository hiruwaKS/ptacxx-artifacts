// <svf-test-suite>@64f017e/src/path_tests/path6.c

#include <stdio.h>


int main(){
    int **p,*q;
    int *a,*b,c,d;
    if(a){
        p = &a;
        q = &c;
    }
    else if(b) {
        p = &b;
        q = &d;
    }
    else{
      printf("dummy branch\n");
    }
    *p = q;

}
