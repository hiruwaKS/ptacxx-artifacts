// <original>

#include <cstdint>
struct Obj {
  int x;
};
int main() {
  Obj o;
  std::uintptr_t v = reinterpret_cast<std::uintptr_t>(&o);
  v = (v >> 2) << 2;
  Obj* p = reinterpret_cast<Obj*>(v);
  return 0;
}
