// <original>

union U {
  void (*f)();
  long i;
};
void a() {
}
int main() {
  U u;
  u.f = a;
  u.f();
  return 0;
}
