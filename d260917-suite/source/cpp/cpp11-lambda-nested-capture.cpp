// <original>

int main() {
  int a;
  auto f = [&]() {
    auto g = [&]() {};
    g();
  };
  f();
  int* p = &a;
  return 0;
}
