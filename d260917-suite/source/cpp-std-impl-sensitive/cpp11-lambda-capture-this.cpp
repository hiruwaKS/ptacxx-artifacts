// <original>

#include <functional>
struct S {
  int x;
  void run() {
    auto cb = [this]() {};
    cb();
  }
};
int main() {
  S s;
  s.x = 1;
  s.run();
  int* p = &s.x;
  return 0;
}
