// <svf-test-suite>@64f017e/src/basic_cpp_tests/list-2.cpp

#include <list>

using namespace std;

int global_obj;
int *global_ptr = &global_obj;

class A {
  public:
    virtual void f(int *i) const {

    }
};

int main(int argc, char **argv)
{
  int *ptr = &global_obj;

  list<const A*> alist;
  A a;
  alist.push_back(&a);

  const A *aptr = alist.front();

  aptr->f(ptr);

  return 0;
}
