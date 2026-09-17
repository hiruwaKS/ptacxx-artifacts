// <original>

#include <variant>
int main() {
  int a;
  std::variant<int*, int> v;
  v = &a;
  int* p = std::get_if<int*>(&v) ? *std::get_if<int*>(&v) : nullptr;
  return 0;
}
