// <original>

#include <functional>
int main() {
  int a;
  std::function<void()> f = [a]() { (void)a; };
  f();
  int* p = &a;
  return 0;
}
