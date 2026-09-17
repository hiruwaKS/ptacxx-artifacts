// <original>

int main() {
  int a;
  auto f = [&a]() { a = 2; };
  f();
  int* p = &a;
  return 0;
}
