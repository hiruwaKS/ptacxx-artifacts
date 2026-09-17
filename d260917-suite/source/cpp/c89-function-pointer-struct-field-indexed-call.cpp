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
  int i = 1;
  s[i].f();
  return 0;
}
