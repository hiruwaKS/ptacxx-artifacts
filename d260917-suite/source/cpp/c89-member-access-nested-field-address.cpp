// <original>

struct Inner {
  int a;
  int b;
};
struct S {
  Inner in;
  int z;
};
int main() {
  S s;
  int* p = &s.in.b;
  return 0;
}
