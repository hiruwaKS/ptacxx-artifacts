// <original>

void a() {
}
int main() {
  void (*f)();
  void (**pp)() = &f;
  *pp = a;
  f();
  return 0;
}
