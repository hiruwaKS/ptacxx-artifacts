// <original>

#include <functional>
void a() {
}
void b() {
}
int main() {
  std::function<void()> f;
  f = std::function<void()>(a);
  f = std::function<void()>(b);
  f();
  return 0;
}
