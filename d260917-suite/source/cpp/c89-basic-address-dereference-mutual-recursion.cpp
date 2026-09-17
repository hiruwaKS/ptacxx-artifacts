// <original>

void b(int* p, int n);
void a(int* p, int n) {
  if (n == 0)
    return;
  else
    b(p, n - 1);
}
void b(int* p, int n) {
  a(p, n);
}
int main() {
  int x;
  a(&x, 2);
  int* p = &x;
  return 0;
}
