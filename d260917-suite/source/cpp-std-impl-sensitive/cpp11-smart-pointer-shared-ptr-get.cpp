// <original>

#include <memory>
std::shared_ptr<int> mk(int* x) {
  return std::shared_ptr<int>(x);
}
int main() {
  int* a = new int;
  auto sp = mk(a);
  int* p = sp.get();
  return 0;
}
