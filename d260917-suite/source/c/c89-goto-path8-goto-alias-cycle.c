// <svf-test-suite>@64f017e/src/path_tests/path8.c

#include <stdio.h>


int main(){

    int **p,*q;
    int *b,*c,d,e;

    p = &c;

c1:    if(e){
           p = &b;
           q = &d;
       }
       else if(b) {
           q = &e;
       }
       else if(c){
          printf("dummy branch\n");
       }
       else{
           goto c1;
       }

       *p = q;

}
