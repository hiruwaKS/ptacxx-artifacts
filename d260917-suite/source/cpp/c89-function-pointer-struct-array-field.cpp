// <original>

struct S {
  void (*f)();
};
void a() {
}
void b() {
}
int main() {
  S s[2];
  s[1].f = b;
  s[1].f();
  return 0;
}
