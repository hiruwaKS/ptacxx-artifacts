// <original>

struct S {
  void (*f)();
};
void a() {
}
int main() {
  S s;
  s.f = a;
  S t;
  t.f = s.f;
  t.f();
  return 0;
}
