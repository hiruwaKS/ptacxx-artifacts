// <original>

struct A {
  virtual void f() {
  }
};
struct B : virtual A {
  void f() {
  }
};
struct C : virtual A {
  void f() {
  }
};
struct D : B, C {
  void f() {
  }
};
int main() {
  A* p = new D;
  p->f();
  return 0;
}
