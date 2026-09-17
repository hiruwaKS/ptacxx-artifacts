// <svf-test-suite>@64f017e/src/basic_cpp_tests/vector-2.cpp

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

  vector<A*> vec;
  A *a = new A;
  vec.push_back(a);

  const A *aptr = vec[0];
  aptr->f(ptr);

  return 0;
}
