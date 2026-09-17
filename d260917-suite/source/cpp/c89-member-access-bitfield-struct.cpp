// <original>

struct B {
  unsigned a : 3;
  unsigned b : 5;
};
int main() {
  B b;
  b.b = 1;
  B* p = &b;
  return 0;
}
