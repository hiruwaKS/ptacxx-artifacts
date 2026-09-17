// <original>

#include <functional>
struct S {
  std::function<void()> f;
};
void a() {
}
int main() {
  S s[2];
  s[1].f = std::function<void()>(a);
  int i = 1;
  s[i].f();
  return 0;
}
