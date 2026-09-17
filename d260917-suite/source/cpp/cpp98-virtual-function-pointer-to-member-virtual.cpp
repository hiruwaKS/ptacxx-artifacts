// <original>

struct A {
  virtual void f() {
  }
};
int main() {
  A o;
  void (A::*pf)() = &A::f;
  (o.*pf)();
  return 0;
}
