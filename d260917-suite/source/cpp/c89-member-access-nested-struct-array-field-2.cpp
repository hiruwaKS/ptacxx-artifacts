// <original>

struct I {
  int* a[2];
};
struct O {
  I in;
};
int main() {
  int x;
  O o;
  o.in.a[1] = &x;
  int* p = o.in.a[1];
  return 0;
}
