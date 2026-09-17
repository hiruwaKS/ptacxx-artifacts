// <original>

#include <memory>
struct S {
  int x;
  int y;
};
int main() {
  auto sp = std::make_shared<S>();
  int* p = &sp->x;
  return 0;
}
