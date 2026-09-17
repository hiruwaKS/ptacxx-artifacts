// <svf-test-suite>@64f017e/src/mem_leak/malloc57.c

#include <stdlib.h>
int main(){
    int* newfile = malloc(190);
    int i = 0;
    if(newfile==NULL){
        return 0;
    }
    for( ; i < 10; i++)
    {
    }

    free(newfile);
    return 0;
}
