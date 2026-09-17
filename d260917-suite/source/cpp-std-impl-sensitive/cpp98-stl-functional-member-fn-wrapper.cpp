// <original>

#include <functional>
struct S {
  std::function<void()> f;
  void run() {
    f();
  }
};
void a() {
}
int main() {
  S s;
  s.f = std::function<void()>(a);
  s.run();
  return 0;
}
