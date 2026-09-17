// <original>

#include <functional>
int main() {
  int a;
  std::function<void()> f = [&]() {};
  f();
  int* p = &a;
  return 0;
}
