// <original>

struct S {
  void (*f)();
};
static void a() {
}
int main() {
  S arr[2];
  arr[1].f = a;
  arr[1].f();
  return 0;
}
