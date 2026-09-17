// <svf-test-suite>@64f017e/src/ae_recursion_tests/recursive_id_8.c

#include "stdbool.h"
#include "stdio.h"

int id(int x);
int id2(int x);

int id(int x) {
    if (x==0) return 0;
    int ret = id2(x-1) + 1;
    if (ret > 3) return 3;
    return ret;
}

int id2(int x) {
    if (x==0) return 0;
    int ret = id(x-1) + 1;
    if (ret > 3) return 3;
    return ret;
}

int main(){
    int x = 3;
    if(x >= 0){
        int res = id(x);

    }
}
