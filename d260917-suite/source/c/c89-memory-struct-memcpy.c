// <svf-test-suite>@64f017e/src/basic_c_tests/structcopy1.c

#include <string.h>


#include <stdlib.h>
struct innerStruct{
int m;
int* n;
};
struct myStruct{
float a;
struct innerStruct b;
};

int main(){
  struct myStruct x;
  x.b.n = malloc(10);
  struct myStruct y;
  memcpy(&y,&x,sizeof(struct myStruct));

}
