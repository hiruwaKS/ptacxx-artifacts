// <original>

struct A {
  virtual int* f() {
    return 0;
  }
};
struct B : A {
  int* f() {
    return 0;
  }
};
int main() {
  int a;
  A* p = new B;
  (void)p;
  int* q = &a;
  return 0;
}
