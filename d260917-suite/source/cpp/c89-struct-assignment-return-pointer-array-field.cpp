// <original>

struct S {
  int* a[2];
};
S mk(int* x) {
  S s;
  s.a[0] = x;
  return s;
}
int main() {
  int x;
  S s = mk(&x);
  int* p = s.a[0];
  return 0;
}
