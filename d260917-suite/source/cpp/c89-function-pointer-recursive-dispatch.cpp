// <original>

void f1(void (*d)(), int n);
void a() {
}
void f2(void (*d)(), int n) {
  if (n == 0)
    d();
  else
    f1(d, n - 1);
}
void f1(void (*d)(), int n) {
  if (n == 0)
    d();
  else
    f2(d, n - 1);
}
int main() {
  f1(a, 3);
  return 0;
}
