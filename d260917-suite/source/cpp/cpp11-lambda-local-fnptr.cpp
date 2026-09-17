// <original>

void a() {
}
int main() {
  auto f = [&]() {
    void (*g)() = a;
    g();
  };
  f();
  return 0;
}
