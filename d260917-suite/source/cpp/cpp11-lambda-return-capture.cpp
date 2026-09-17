// <original>

auto mk(int* x) {
  return [&]() {};
}
int main() {
  int a;
  auto f = mk(&a);
  f();
  int* p = &a;
  return 0;
}
