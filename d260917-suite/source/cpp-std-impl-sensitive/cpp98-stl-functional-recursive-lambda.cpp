// <original>

#include <functional>
std::function<int(int)> fib;
int main() {
  int a;
  fib = [&](int n) -> int {
    if (n <= 1)
      return 1;
    return fib(n - 1);
  };
  int r = fib(3);
  (void)r;
  int* p = &a;
  return 0;
}
