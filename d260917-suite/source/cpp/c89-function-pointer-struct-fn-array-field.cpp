// <original>

struct S {
  void (*t[2])();
};
void a() {
}
int main() {
  S s;
  s.t[1] = a;
  int i = 1;
  s.t[i]();
  return 0;
}
