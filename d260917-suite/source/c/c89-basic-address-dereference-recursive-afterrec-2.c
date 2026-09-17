// <svf-test-suite>@64f017e/src/ae_recursion_tests/recursive_afterrec_2.c

#include "stdbool.h"

void f(int);
void f2(int);

int g;

void f(int n) {
    if (n<3){
        g = 3;
        return;
    }
    n--;
    f2(n);
}

void f2(int n) {
    if (n<3){
        g = 3;
        return;
    }
    n--;
    f(n);
}

int main(){
    f(4);

}
