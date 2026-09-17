// <svf-test-suite>@64f017e/src/basic_cpp_tests/member-variable.cpp

int global_obj_a;
int *global_ptr_a = &global_obj_a;

int global_obj_b;
int *global_ptr_b = &global_obj_b;

class A {
  public:
    virtual void f(int *i) {

    }
};

class B {
  public:
    B(A *a): _a(a) {}
    virtual void f(int *i) {

    }
    A *_a;
};

int main(int argc, char **argv)
{
  int *i = &global_obj_a;
  int *j = &global_obj_b;

  A *a = new A;
  B *b = new B(a);

  b->f(j);

  b->_a->f(i);

  return 0;
}
