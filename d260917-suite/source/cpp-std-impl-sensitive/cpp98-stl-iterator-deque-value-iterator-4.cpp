// <svf-test-suite>@64f017e/src/basic_cpp_tests/deque-4.cpp

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

  deque<A>::iterator it = adeque.begin();
  const A *aptr = &*it;

  aptr->f(ptr);

  return 0;
}
