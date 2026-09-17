// <svf-test-suite>@64f017e/src/double_free/df2.c

#include <stdlib.h>
int main(){
    int *i = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    free(i);
    i = malloc(sizeof(int));
    free(i);
    i = 0;
    free(i);
    free(b);
}
