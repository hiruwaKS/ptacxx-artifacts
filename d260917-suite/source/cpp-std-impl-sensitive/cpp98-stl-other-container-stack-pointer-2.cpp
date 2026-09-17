// <svf-test-suite>@64f017e/src/basic_cpp_tests/stack-2.cpp

#include <iostream>
#include <stack>

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

  stack<const A*> astack;
  A a;
  astack.push(&a);

  const A *aptr = astack.top();
  astack.pop();
  aptr->f(ptr);

  return 0;
}
