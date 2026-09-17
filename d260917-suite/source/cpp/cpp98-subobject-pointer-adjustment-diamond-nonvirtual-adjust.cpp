// <svf-test-suite>@64f017e/src/basic_cpp_tests/diamond-inheritance.cpp

int global_obj_b;
int *global_ptr_b = &global_obj_b;

int global_obj_c;
int *global_ptr_c = &global_obj_c;

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

class C: public A {
  public:
    virtual void f(int *i) {

    }
};

class D: public B, public C {
};

int main()
{
  int *ptr_b = &global_obj_b;
  int *ptr_c = &global_obj_c;

  D d;

  B *b = &d;
  b->f(ptr_b);

  C *c = &d;
  c->f(ptr_c);

  return 0;
}
