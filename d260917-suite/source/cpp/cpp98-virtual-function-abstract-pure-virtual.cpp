// <svf-test-suite>@64f017e/src/basic_cpp_tests/abstract.cpp

int global_obj_f;
int *global_ptr_f = &global_obj_f;

int global_obj_g;
int *global_ptr_g = &global_obj_g;

class A {
  public:
    virtual void f(int *i) = 0;
    virtual void g(int *i) {

    }
};

class B: public A {
  public:
    virtual void f(int *i) {

    }
    virtual void g(int *i) {

    }
};

int main()
{
  int *ptr_f = &global_obj_f;
  int *ptr_g = &global_obj_g;

  A *a = new B;
  a->f(ptr_f);
  a->g(ptr_g);

  return 0;
}
