// <original>

void a() {
}
int main() {
  void (*t[2])() = {a, a};
  void (**p)() = t;
  void (*f)() = *(p + 1);
  f();
  return 0;
}
