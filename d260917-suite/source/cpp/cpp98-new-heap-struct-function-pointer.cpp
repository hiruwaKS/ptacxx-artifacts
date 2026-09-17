// <original>

struct S {
  void (*f)();
};
void a() {
}
int main() {
  S* s = new S;
  s->f = a;
  s->f();
  return 0;
}
