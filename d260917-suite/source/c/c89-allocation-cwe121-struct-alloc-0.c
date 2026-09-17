// <svf-test-suite>@64f017e/src/ae_assert_tests/cwe121_struct_alloc-0.c

#include <string.h>
#include "stdbool.h"
#include <alloca.h>
#define ALLOCA alloca

typedef struct _twoIntsStruct
{
    int intOne;
    int intTwo;
} twoIntsStruct;

int main() {
    twoIntsStruct * data;
    twoIntsStruct * dataBadBuffer = (twoIntsStruct *)ALLOCA((4)*sizeof(twoIntsStruct));

    data = dataBadBuffer;
    data[0].intOne = 10;
    data[1].intOne = 11;
    data[2].intOne = 12;

}
