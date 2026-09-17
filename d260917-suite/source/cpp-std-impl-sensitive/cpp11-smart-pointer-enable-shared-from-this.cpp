// <original>

#include <memory>
struct S : std::enable_shared_from_this<S> {
  int* data;
};
int main() {
  int a = 1;
  auto sp = std::make_shared<S>();
  sp->data = &a;
  S* self = sp->shared_from_this().get();
  int* p = self->data;
  return 0;
}
