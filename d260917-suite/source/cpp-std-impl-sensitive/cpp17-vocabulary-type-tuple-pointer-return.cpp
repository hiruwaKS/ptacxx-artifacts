// <original>

#include <tuple>
using namespace std;
tuple<int, int*> f(int* x) {
  return make_tuple(1, x);
}
int main() {
  int a = 1;
  tuple<int, int*> t = f(&a);
  int* p = get<1>(t);
  return 0;
}
