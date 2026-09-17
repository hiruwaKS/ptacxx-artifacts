// <svf-test-suite>@64f017e/src/ae_recursion_tests/recursive_id_5_no-main.c

#include "stdbool.h"
#include "stdio.h"

unsigned int id(unsigned int x);
unsigned int id2(unsigned int x);

unsigned int id(unsigned int x) {
    if (x==0) return 0;
    unsigned int ret = id2(x-1) + 1;
    if (ret > 2) return 2;
    return ret;
}

unsigned int id2(unsigned int x) {
    if (x==0) return 0;
    unsigned int ret = id(x-1) + 1;
    if (ret > 2) return 2;
    return ret;
}

int no_main_recursive_id_5(){
    int x;
    scanf("%ud", &x);

    int res = id(x);

}

int main(){
    unsigned int x = 5;
    unsigned int res = id(x);
    (void)res;
    return 0;
}
