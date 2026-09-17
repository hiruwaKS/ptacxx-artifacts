// <original>

void f(int* p, int n) {
  if (n == 0)
    return;
  else
    f(p, n - 1);
}
int main() {
  int a;
  f(&a, 2);
  int* p = &a;
  return 0;
}
