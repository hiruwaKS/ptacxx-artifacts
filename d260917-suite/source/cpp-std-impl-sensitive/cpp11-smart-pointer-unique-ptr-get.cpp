// <original>

#include <memory>
std::unique_ptr<int> mk(int* x) {
  return std::unique_ptr<int>(x);
}
int main() {
  int* a = new int;
  auto u = mk(a);
  int* p = u.get();
  return 0;
}
