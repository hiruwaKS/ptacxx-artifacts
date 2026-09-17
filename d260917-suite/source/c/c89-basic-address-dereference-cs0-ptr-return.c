// <svf-test-suite>@64f017e/src/cs_tests/cs0.c

int* foo(int* x){
   return x;
}

int main(){

  int *x,*y,*p,*q,a,b;
  p = &a;
  q = &b;
  x = foo(p);
  y = foo(q);

}
