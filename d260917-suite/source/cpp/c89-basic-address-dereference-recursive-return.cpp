// <original>

int* f(int* p, int n) {
  if (n == 0)
    return p;
  return f(p, n - 1);
}
int main() {
  int a;
  int* p = f(&a, 2);
  return 0;
}
