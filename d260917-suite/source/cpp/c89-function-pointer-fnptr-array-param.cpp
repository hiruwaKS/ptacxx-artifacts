// <original>

void a() {
}
void b() {
}
void call(void (*t[])(), int i) {
  t[i]();
}
int main() {
  void (*t[2])() = {a, b};
  call(t, 1);
  return 0;
}
