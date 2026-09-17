// <original>

#include <functional>
struct S {
  std::function<void()> f;
};
S mk() {
  S s;
  s.f = std::function<void()>();
  return s;
}
void a() {
}
int main() {
  S s = mk();
  s.f = a;
  s.f();
  return 0;
}
