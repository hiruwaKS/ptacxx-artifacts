// <original>

struct S {
  void f() {
  }
};
int main() {
  S s;
  void (S::*pf)() = &S::f;
  (s.*pf)();
  return 0;
}
