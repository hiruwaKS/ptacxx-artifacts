// <original>

struct S {
  void (*f)();
};
static void a() {
}
int main() {
  S arr[2];
  arr[1].f = a;
  int i = 1;
  arr[i].f();
  return 0;
}
