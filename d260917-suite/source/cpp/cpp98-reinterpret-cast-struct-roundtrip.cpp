// <original>

struct A {
  int* p;
};
struct B {
  int q;
};
int main() {
  int a;
  A x;
  x.p = &a;
  B* b = reinterpret_cast<B*>(&x);
  A* y = reinterpret_cast<A*>(b);
  int* p = y->p;
  return 0;
}
