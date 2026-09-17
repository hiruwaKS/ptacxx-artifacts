// <original>

int main() {
  int a;
  auto f = [](int* x) { (void)x; };
  f(&a);
  int* p = &a;
  return 0;
}
