// <original>

struct A {
  void f() {
  }
};
struct S {
  void (A::*pf)();
  A* o;
};
int main() {
  A o;
  S s;
  s.o = &o;
  s.pf = &A::f;
  (s.o->*(s.pf))();
  return 0;
}
