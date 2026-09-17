// <original>

#include <functional>
void a() {
}
int main() {
  std::function<void()> f[2];
  f[1] = a;
  int i = 1;
  f[i]();
  return 0;
}
