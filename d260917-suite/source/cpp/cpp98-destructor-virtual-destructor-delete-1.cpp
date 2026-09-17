// <svf-test-suite>@64f017e/src/basic_cpp_tests/destructor-1.cpp

int global_obj;
int *global_ptr = &global_obj;

class A {
  public:
    A(int *i): aptr(i) {}
    virtual ~A() { f(); }
    virtual void f() {  }
  private:
    int *aptr;
};

class B: public A {
  public:
    B(int *i): A(i), bptr(i) {}
    virtual ~B() { f(); }
    virtual void f() {  }
  private:
    int *bptr;
};

int main(void)
{
  int *i = &global_obj;

  B *b = new B(i);

  delete b;

  return 0;
}
