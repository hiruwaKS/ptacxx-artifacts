// <svf-test-suite>@64f017e/src/ae_recursion_tests/recursive_id_3.c

#include "stdbool.h"
#include "stdio.h"

int id(int x) {
    if (x==0) return 0;
    int ret = id(x-1) + 1;
    if (ret > 3) return 3;
    return ret;
}

int main(){
    int x = 3;
    if(x >= 0) {
        int res = id(x);

    }
}
