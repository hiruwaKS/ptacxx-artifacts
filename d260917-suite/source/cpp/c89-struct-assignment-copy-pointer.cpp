// <original>

struct S {
  int* p;
};
int main() {
  int a;
  S s;
  s.p = &a;
  S t = s;
  int* q = t.p;
  return 0;
}
