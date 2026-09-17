// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
struct Holder {
  A* a;
};
int main() {
  Holder h;
  h.a = new B;
  h.a->f();
  return 0;
}
