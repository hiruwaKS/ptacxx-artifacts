// <svf-test-suite>@64f017e/src/ae_assert_tests/BASIC_ptr_func_6-0.c

#include "stdbool.h"
static int nd_int(void) { return 0; }
void c (int*);

int main(int argc, char** argv) {
  void (*q) (int*) = c;
  nd_int();

  int y = 5;
  q(&y);

}

void c(int* x) {
  *x = *x+5;
  nd_int();
}
