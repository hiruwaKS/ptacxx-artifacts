// <original>

struct A {
  virtual void f() {
  }
};
struct B : A {
  void f() {
  }
};
A* gp = new B;
int main() {
  gp->f();
  return 0;
}
