// <original>

struct I {
  int x;
  int y;
};
struct O {
  I inner;
};
int main() {
  O o;
  int* py = &o.inner.y;
  O* po = (O*)((char*)py - 4);
  return 0;
}
