// <original>

struct S {
  int* p;
};
int main() {
  int a;
  S s[4];
  int i = 2;
  s[i].p = &a;
  int* q = s[i].p;
  return 0;
}
