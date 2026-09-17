// <original>

struct S {
  void (*f)();
};
S g;
void x();
void y() {
  g.f = x;
}
void x() {
  g.f = y;
}
int main() {
  g.f = y;
  g.f();
  return 0;
}
