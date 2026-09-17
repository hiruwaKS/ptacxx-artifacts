// <original>

#include <any>
using namespace std;
any f(int* x) {
  return x;
}
int main() {
  int a = 1;
  any o = f(&a);
  int* p = any_cast<int*>(o);
  return 0;
}
