// <original>

#include <functional>
void call(std::function<void()> cb) {
  cb();
}
int main() {
  int a;
  std::function<void()> f = [&]() {};
  call(f);
  int* p = &a;
  return 0;
}
