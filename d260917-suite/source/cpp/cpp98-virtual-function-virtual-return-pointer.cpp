// <original>

struct A {
  virtual int* get() {
    return 0;
  }
};
struct B : A {
  int* get() {
    return p;
  }
  int* p;
};
int main() {
  int a;
  B b;
  b.p = &a;
  A* ap = &b;
  int* q = ap->get();
  return 0;
}
