// <svf-test-suite>@64f017e/src/basic_cpp_tests/virtual-inheritance-1.cpp

int global_obj;
int *global_ptr = &global_obj;

class A {
  public:
    virtual void f(int *i) {

    }
};

class B: virtual public A {
};

int main(int argc, char **argv)
{
  int *ptr = &global_obj;

  A *pb = new B;
  pb->f(ptr);

  return 0;
}
