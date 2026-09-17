// <svf-test-suite>@64f017e/src/ae_recursion_tests/recursive_afterrec_1.c

#include "stdbool.h"

int g;

void f(int n) {
    if (n<3){
        g = 3;
        return;
    }
    n--;
    f(n);
}

int main(){
    f(10);

}
