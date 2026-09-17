// <original>

struct Cb {
  void (*f)();
};
void a() {
}
Cb g;
void reg() {
  g.f = a;
}
void fire() {
  g.f();
}
int main() {
  reg();
  fire();
  return 0;
}
