// <original>

#include <functional>
struct S {
  void f() {
  }
};
int main() {
  S s;
  std::function<void()> cb = std::bind(&S::f, &s);
  cb();
  return 0;
}
