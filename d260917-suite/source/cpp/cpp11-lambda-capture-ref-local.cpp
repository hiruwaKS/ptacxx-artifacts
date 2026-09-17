// <original>

int main() {
  int a;
  auto f = [&a]() {};
  f();
  int* p = &a;
  return 0;
}
