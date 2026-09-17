// <svf-test-suite>@64f017e/src/complex_tests/test.c

#include <stdlib.h>

typedef struct{
    int * b;
    int * a;
} basestruct;

typedef struct {
    int * b;
    basestruct * a;
    unsigned temp;
} extendstruct;

extendstruct gvar[10];

int * saveptr[5];
int i;

void save(basestruct ** var) {
    unsigned idx = i;
    int * temp = var;
    saveptr[idx] = (int *)(var);
    saveptr[idx+1] = (int *)(*var);
}

void f() {
    int local;
    gvar[0].a = malloc(sizeof(basestruct));
    gvar[0].a->a = &local;
    save (&gvar[0]);

    basestruct * temp = saveptr[i];
    extendstruct * t1 = (extendstruct *) temp;

    basestruct * t2 = t1->a;
    *(t2->a) = 0;
}

int main(void) {
    f();
    return 0;
}
