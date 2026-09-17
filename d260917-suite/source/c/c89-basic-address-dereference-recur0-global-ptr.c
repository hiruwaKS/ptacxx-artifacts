// <svf-test-suite>@64f017e/src/cs_tests/recur0.c

int *x, y, z;

void f() {
  if(z > 5) return;
  z++;
  if (1) {
         x = &y;

          f();
         x = &z;

          f();
  }
}

int main()
{
           f();
	   return 0;
}
