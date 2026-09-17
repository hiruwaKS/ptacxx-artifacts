// <original>

struct A {
  virtual void f() {
  }
};
int main() {
  A* p = new A;
  auto cb = [&]() { p->f(); };
  cb();
  return 0;
}
