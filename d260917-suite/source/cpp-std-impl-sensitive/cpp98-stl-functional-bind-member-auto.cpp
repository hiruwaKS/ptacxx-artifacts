// <original>

#include <functional>
struct S {
  void f() {
  }
};
int main() {
  S s;
  auto cb = std::bind(&S::f, &s);
  cb();
  return 0;
}
