// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
int main() {
  A* p = new B;
  p->f();
  return 0;
}
