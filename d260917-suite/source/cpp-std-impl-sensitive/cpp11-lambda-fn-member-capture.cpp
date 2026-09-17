// <original>

#include <functional>
struct S {
  void f() {
  }
};
int main() {
  S s;
  std::function<void()> cb = [&] { s.f(); };
  cb();
  return 0;
}
