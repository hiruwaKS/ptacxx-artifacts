// <original>

struct I {
  int* p;
};
struct O {
  I in;
};
O mk(int* x) {
  O o;
  o.in.p = x;
  return o;
}
int main() {
  int x;
  O o = mk(&x);
  int* p = o.in.p;
  return 0;
}
