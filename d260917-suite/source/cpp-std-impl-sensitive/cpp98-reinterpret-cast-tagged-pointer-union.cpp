// <original>

#include <cstdint>

struct A {
  int x;
};
struct B {
  int y;
};

class PUnion {
  union {
    std::uintptr_t Value;
  };
  static const unsigned TagBits = 1;
  static const std::uintptr_t TagMask = (std::uintptr_t{1} << TagBits) - 1;

public:
  explicit PUnion(A* p) : Value(reinterpret_cast<std::uintptr_t>(p)) {
  }
  explicit PUnion(B* p) : Value(reinterpret_cast<std::uintptr_t>(p) | 1) {
  }
  A* getA() const {
    return reinterpret_cast<A*>(Value & ~TagMask);
  }
};

int main() {
  A a;
  PUnion pu(&a);
  A* q = pu.getA();
  return 0;
}
