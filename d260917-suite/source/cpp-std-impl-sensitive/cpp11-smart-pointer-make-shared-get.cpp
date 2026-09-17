// <original>

#include <memory>
struct S {
  int x;
  int y;
};
int main() {
  auto sp = std::make_shared<S>();
  S* p = sp.get();
  return 0;
}
