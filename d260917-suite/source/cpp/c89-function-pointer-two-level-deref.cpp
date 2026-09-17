// <original>

void a() {
}
int main() {
  void (*f)() = a;
  void (**g)() = &f;
  void (*h)() = *g;
  h();
  return 0;
}
