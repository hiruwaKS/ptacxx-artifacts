// <original>

struct A {
  void f() {
  }
};
int main() {
  A* o = new A;
  void (A::*pf)() = &A::f;
  (o->*pf)();
  return 0;
}
