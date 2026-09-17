// <svf-test-suite>@64f017e/src/basic_cpp_tests/forward_list-1.cpp

#include <iostream>
#include <forward_list>

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

  forward_list<const A*> alist;
  A *a = new A;

  alist.push_front(a);

  const A *aptr = alist.front();

  aptr->f(ptr);

  return 0;
}
