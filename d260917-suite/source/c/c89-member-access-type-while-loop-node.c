// <svf-test-suite>@64f017e/src/objtype_tests/type-while.c

#include <stdlib.h>
struct MyStruct {
    int * f1;
    struct MyStruct * next;
};

int main() {
    struct MyStruct * p = (struct MyStruct *) malloc(sizeof(struct MyStruct));

    int num = 10;
    while (num) {
        p->next = (struct MyStruct *) malloc(sizeof(struct MyStruct));
        p->next->f1 = (int *) malloc(sizeof(int));
        p = p->next;
        num--;
    }
    struct MyStruct *q = p;
    return 0;
}
