// <original>

#include <memory>
struct S {
  int x;
  int y;
};
int main() {
  auto sp = std::make_shared<S>();
  std::shared_ptr<int> a(sp, &sp->x);
  int* p = a.get();
  int* q = &sp->x;
  return 0;
}
