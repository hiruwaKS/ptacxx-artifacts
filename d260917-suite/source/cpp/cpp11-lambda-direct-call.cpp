// <original>

int main() {
  int a;
  auto f = [&]() {};
  f();
  int* p = &a;
  return 0;
}
