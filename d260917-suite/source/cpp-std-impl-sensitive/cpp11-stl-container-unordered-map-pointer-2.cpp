// <svf-test-suite>@64f017e/src/basic_cpp_tests/unordered_map-2.cpp

#include <iostream>
#include <unordered_map>

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

  unordered_map<int, const A*> amap;
  A a;
  amap[0] = &a;

  unordered_map<int, const A*>::const_iterator it = amap.begin();
  const A *aptr = it->second;
  aptr->f(ptr);

  return 0;
}
