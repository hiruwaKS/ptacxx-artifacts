// <svf-test-suite>@64f017e/src/basic_c_tests/byteoffset1.c

#include <stdio.h>
#include <stdlib.h>


__attribute__((noinline))
void MAYALIAS(void* p, void* q){
  printf("%c%c\n", p, q);
}

typedef struct StructA
{
    int foo;
    int (*f)(void);
} StructA;

__attribute__((noinline))
int FuncA() {
    return 1;
}

__attribute__((noinline))
int CallF(StructA *structA) {
    int ret = structA->f();
    MAYALIAS(structA->f, &FuncA);
    return ret;
}

int main() {
    StructA *structA = malloc(sizeof(StructA));
    structA->f = FuncA;

    int ret = CallF(structA);
    (void)ret;
    return 0;
}
