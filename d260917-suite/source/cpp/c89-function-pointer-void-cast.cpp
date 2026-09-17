// <original>

void a() {
}
int main() {
  void* v = (void*)(void (*)(void))a;
  void (*f)() = (void (*)(void))v;
  f();
  return 0;
}
