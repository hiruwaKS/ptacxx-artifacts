// <original>

int main() {
  int a;
  auto f = [&]() {};
  int* p = &a;
  f();
  return 0;
}
