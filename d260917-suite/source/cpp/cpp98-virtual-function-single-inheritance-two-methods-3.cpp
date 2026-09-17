// <svf-test-suite>@64f017e/src/basic_cpp_tests/single-inheritance-3.cpp

int global_int_obj;
int *global_int_ptr = &global_int_obj;

float global_float_obj;
float *global_float_ptr = &global_float_obj;

class A {
  public:
  virtual void f(int *i) {

  }
  virtual void g(float *j) {

  }
};

class B: public A {
  public:
  virtual void f(int *i) {

  }
  virtual void g(float *j) {

  }
};

int main(int argc, char **argv)
{
  int *i = &global_int_obj;
  float *j = &global_float_obj;

  A *p = new B;

  p->f(i);
  p->g(j);

  return 0;
}
