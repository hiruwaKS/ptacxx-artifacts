// <original>

#include <cstdint>

struct Obj {
  int x;
};
enum State { S0, S1 };

class PtrInt {
  union {
    std::uintptr_t Value;
    Obj* PtrVal;
  };
  static const unsigned NumLowBits = 2;
  static const std::uintptr_t Mask =
      ~((std::uintptr_t)(std::uintptr_t{1} << NumLowBits) - 1);

public:
  explicit PtrInt(Obj* P, State I) {
    set(P, I);
  }
  void set(Obj* Ptr, State IntVal) {
    Value = reinterpret_cast<std::uintptr_t>(Ptr);
    Value |= static_cast<std::uintptr_t>(IntVal);
  }
  Obj* getPointer() const {
    return reinterpret_cast<Obj*>(Value & Mask);
  }
};

int main() {
  Obj o;
  PtrInt pi(&o, S1);
  Obj* q = pi.getPointer();
  return 0;
}
