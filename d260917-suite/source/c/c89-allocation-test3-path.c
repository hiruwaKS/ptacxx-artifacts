// <svf-test-suite>@64f017e/src/complex_tests/test3-path.c

#include <stdlib.h>
char * h() {
   char * a = malloc(20);
   return a;
}

char * g() {
    char * a = malloc(10);
    return a;
}

char * f(int flag) {
   if (flag == 1) return h();
   else return g();
}

int main (){
    char a[20];
    int flag = a[0];
    char * pa, * pb;

    pa = malloc(1); pb = malloc(1);
    if (flag == 1) {
       pa = f(flag);
    }
    else  {
       pb = f(flag);
    }
    * pa = 0;
    * pb = 1;
}
