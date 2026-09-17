// <original>

struct S {
  void (*f)();
};
static void a() {
}
int main() {
  S s;
  s.f = a;
  S t = s;
  t.f();
  return 0;
}
