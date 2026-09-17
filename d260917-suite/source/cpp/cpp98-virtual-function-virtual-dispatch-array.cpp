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
  A* arr[2];
  arr[1] = new B;
  int i = 1;
  arr[i]->f();
  return 0;
}
