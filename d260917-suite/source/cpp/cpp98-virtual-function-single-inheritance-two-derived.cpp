// <svf-test-suite>@64f017e/src/failed_tests/single-inheritance-5.cpp

int global_obj;
int *global_ptr = &global_obj;

class A {
  public:
    virtual void f(int *i) {

    }
};

class B: public A {
    virtual void f(int *i) {

    }
};

class C: public A {
    virtual void f(int *i) {

    }
};

int main(int argc, char **argv)
{
  int *ptr = &global_obj;

  A *pb;
  if(ptr)
  pb = new C;
  else
  pb = new B;
  pb->f(ptr);

  return 0;
}
