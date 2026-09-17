// <original>

struct A {
  virtual void f() {
  }
  virtual void g() {
    f();
  }
};
struct B : A {
  void f() {
  }
};
int main() {
  A* p = new B;
  p->g();
  return 0;
}
