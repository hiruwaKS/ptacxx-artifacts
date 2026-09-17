// <original>

void a() {
}
void (*getA())(void) {
  return a;
}
int main() {
  void (*f)() = getA();
  f();
  return 0;
}
