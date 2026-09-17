// <original>

void a() {
}
void b() {
}
int main() {
  void (*f)() = a;
  void (*g)() = b;
  void (**p)() = &f;
  void** q = (void**)p;
  void (*h)() = (void (*)(void)) * q;
  h();
  return 0;
}
