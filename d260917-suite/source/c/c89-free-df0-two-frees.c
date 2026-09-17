// <svf-test-suite>@64f017e/src/double_free/df0.c

#include <stdlib.h>
int main(){
    int *i = malloc(sizeof(int));
    free(i);
    i = 0;
    free(i);
}
