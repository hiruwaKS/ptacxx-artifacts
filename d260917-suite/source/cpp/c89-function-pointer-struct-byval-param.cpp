// <original>

struct S {
  void (*f)();
};
void a() {
}
void call(S s) {
  s.f();
}
int main() {
  S s;
  s.f = a;
  call(s);
  return 0;
}
