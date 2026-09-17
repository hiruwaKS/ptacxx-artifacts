// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
A* make() {
  return new B;
}
int main() {
  A* p = make();
  p->f();
  return 0;
}
