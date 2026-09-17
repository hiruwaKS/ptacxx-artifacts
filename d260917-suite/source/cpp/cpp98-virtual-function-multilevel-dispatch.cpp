// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
struct C : B {
  void f() {
  }
};
int main() {
  A* p = new C;
  p->f();
  return 0;
}
