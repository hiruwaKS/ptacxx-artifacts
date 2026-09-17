// <svf-test-suite>@64f017e/src/failed_tests/test-recursion1.c

#include <stdlib.h>

typedef struct{
    int t1;
    int t2;
    int * b;
    int * a;
} basestruct;

static int depth = 0;

void f(basestruct * a) {
    int * t = a->b;
    basestruct * t1 = &(a->b);
    if(depth < 2){
        depth++;
        f(t1);
    }

    a->b = a;
}

int main(){
  basestruct t;
  f(&t);
  return 0;
}
