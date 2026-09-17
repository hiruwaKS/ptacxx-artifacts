// <svf-test-suite>@64f017e/src/basic_cpp_tests/map-2.cpp

#include <iostream>
#include <map>

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

  map<int, const A*> amap;
  A a;
  amap.insert(pair<int, const A*>(0, &a));

  map<int, const A*>::const_iterator it = amap.begin();
  const A *aptr = it->second;
  aptr->f(ptr);

  return 0;
}
