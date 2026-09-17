// <original>

struct S {
  int* p;
};
void take(S s) {
}
int main() {
  int a;
  S s;
  s.p = &a;
  take(s);
  int* p = &a;
  return 0;
}
