// <original>

void a() {
}
void (*pick())(void) {
  return a;
}
int main() {
  void (*f)() = pick();
  f();
  return 0;
}
