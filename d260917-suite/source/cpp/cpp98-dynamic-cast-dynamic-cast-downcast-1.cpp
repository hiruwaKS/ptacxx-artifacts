// <svf-test-suite>@64f017e/src/basic_cpp_tests/dynamic_cast-1.cpp

int global_obj;
int *global_ptr = &global_obj;

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
  int *ptr = &global_obj;

  A *pa = new B;

  if (B *pb = dynamic_cast<B*>(pa)) {
    pb->f(ptr);
  }

  return 0;
}
