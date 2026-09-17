// <svf-test-suite>@64f017e/src/basic_cpp_tests/single-inheritance-2.cpp

int global_obj_a;
int *global_ptr_a = &global_obj_a;

int global_obj_b;
int *global_ptr_b = &global_obj_b;

class A {
  public:
    virtual void f(int *i) {

    }
};

class B: public A {
  public:
    virtual void f(int *i) {

    }
};

int main(int argc, char **argv)
{
  int *i = &global_obj_a;
  A *pa = new A;
  pa->f(i);

  int *j = &global_obj_b;
  B *pb = new B;
  pb->f(j);

  return 0;
}
