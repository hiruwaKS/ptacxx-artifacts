// <original>

#include <cstdint>
struct Obj {
  int x;
};
class PtrInt {
  union {
    std::uintptr_t Value;
    Obj* PtrVal;
  };
  static const unsigned N = 3;
  static const std::uintptr_t Mask =
      ~((std::uintptr_t)(std::uintptr_t{1} << N) - 1);

public:
  PtrInt(Obj* p, unsigned s) {
    Value = (std::uintptr_t)p | s;
  }
  Obj* getPointer() const {
    return (Obj*)(Value & Mask);
  }
};
int main() {
  Obj o;
  PtrInt pi(&o, 1);
  Obj* q = pi.getPointer();
  return 0;
}
