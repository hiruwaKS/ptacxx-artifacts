// <original>

#include <memory>

struct Impl {
  int* data;
};
class Foo {
  std::unique_ptr<Impl> impl;

public:
  Foo(int* d) : impl(new Impl{d}) {
  }
  int* get() const {
    return impl->data;
  }
};

int main() {
  int a = 1;
  Foo f(&a);
  int* p = f.get();
  return 0;
}
