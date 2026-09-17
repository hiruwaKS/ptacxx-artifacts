// <original>

#include <array>
using namespace std;
array<int*, 1> f(int* x) {
  return {x};
}
int main() {
  int a = 1;
  array<int*, 1> arr = f(&a);
  int* p = arr[0];
  return 0;
}
