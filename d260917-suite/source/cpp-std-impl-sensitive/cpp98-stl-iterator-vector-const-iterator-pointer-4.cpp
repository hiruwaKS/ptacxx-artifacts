// <svf-test-suite>@64f017e/src/basic_cpp_tests/vector-4.cpp

#include <iostream>
#include <vector>

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

  vector<const A*> vec;
  A a;
  vec.push_back(&a);

  vector<const A*>::const_iterator it = vec.begin();
  const A *aptr = *it;
  aptr->f(ptr);

  return 0;
}
