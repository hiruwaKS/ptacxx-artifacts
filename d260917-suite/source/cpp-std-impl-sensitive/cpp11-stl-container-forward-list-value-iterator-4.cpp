// <svf-test-suite>@64f017e/src/basic_cpp_tests/forward_list-4.cpp

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

  forward_list<A> alist;
  A a;

  alist.push_front(a);

  forward_list<A>::iterator it = alist.begin();
  const A *aptr = &*it;

  aptr->f(ptr);

  return 0;
}
