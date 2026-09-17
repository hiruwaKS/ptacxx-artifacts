// <original>

void a() {
}
void b() {
}
int main() {
  void (*t1[2])() = {a, b};
  void (**t2[2])() = {t1, t1};
  int i = 1;
  void (*f)() = t2[0][i];
  f();
  return 0;
}
