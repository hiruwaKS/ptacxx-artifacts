// <svf-test-suite>@64f017e/src/cs_tests/recur10.c

int **p,*x, y, z;

void f() {
  p = &x;
  if (z) {
    *p = &y;

    f();
    *p = &z;

    f();
  }
}

int main()
{
    f();
    return 0;
}
