// <original>

#include <functional>
void f() {
}
int main() {
  auto cb = std::bind(f);
  cb();
  return 0;
}
