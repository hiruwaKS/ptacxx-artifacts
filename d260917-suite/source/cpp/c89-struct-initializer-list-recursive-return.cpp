// <original>

struct S {
  int* p;
};
S f(int* x, int n) {
  if (n == 0)
    return {x};
  return f(x, n - 1);
}
int main() {
  int a;
  S s = f(&a, 2);
  int* p = s.p;
  return 0;
}
