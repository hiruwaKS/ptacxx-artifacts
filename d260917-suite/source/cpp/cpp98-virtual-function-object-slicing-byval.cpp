// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
A byval() {
  B b;
  return b;
}
int main() {
  A a = byval();
  a.f();
  return 0;
}
