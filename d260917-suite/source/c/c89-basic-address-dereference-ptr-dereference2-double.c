// <svf-test-suite>@64f017e/src/basic_c_tests/ptr-dereference2.c

int main(){

  int **a, *b, *x ,c;
  c = 10;
  a = &b;
  b = &c;
  x = *a;
  int y = *x;

  return 0;
}
