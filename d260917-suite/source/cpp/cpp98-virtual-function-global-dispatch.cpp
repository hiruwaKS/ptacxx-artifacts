// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
A* gp;
int main() {
  A* p = new B;
  gp = p;
  gp->f();
  return 0;
}
