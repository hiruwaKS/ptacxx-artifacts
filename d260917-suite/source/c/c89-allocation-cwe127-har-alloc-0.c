// <svf-test-suite>@64f017e/src/ae_assert_tests/CWE127_har_alloc-0.c

#include <string.h>
#include "stdbool.h"
#include <alloca.h>
#define ALLOCA alloca

int main() {
    char * data;
    char * dataBuffer = (char *)ALLOCA(3*sizeof(char));
    memset(dataBuffer, 'A', 3-1);
    dataBuffer[3-1] = '\0';

    data = dataBuffer;
    char dest[2*2];
    memset(dest, 'C', 2*2-1);
    dest[2*2-1] = '\0';

    strcpy(dest, data);

}
