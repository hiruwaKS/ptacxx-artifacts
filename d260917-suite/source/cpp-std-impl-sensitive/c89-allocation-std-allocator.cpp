// <original>

#include <memory>
int main() {
  int a;
  std::allocator<int*> al;
  int** m = al.allocate(4);
  m[0] = &a;
  int* p = m[0];
  al.deallocate(m, 4);
  return 0;
}
