// <original>

struct Inner {
  int* p;
};
struct Outer {
  Inner in;
};
int main() {
  int a;
  Outer o;
  o.in.p = &a;
  int* q = o.in.p;
  return 0;
}
