// <svf-test-suite>@64f017e/src/basic_cpp_tests/deque-3.cpp

#include <deque>

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

  deque<A> adeque;
  A a;
  adeque.push_back(a);

  const A *aptr = &adeque.front();

  aptr->f(ptr);

  return 0;
}
