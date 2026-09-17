// <original>

struct S {
  void (*f)();
};
S gs;
void a() {
}
int main() {
  gs.f = a;
  gs.f();
  return 0;
}
