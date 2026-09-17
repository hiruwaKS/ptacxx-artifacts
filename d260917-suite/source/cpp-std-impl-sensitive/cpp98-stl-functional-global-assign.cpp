// <original>

#include <functional>
std::function<void()> g;
void a() {
}
int main() {
  g = a;
  g();
  return 0;
}
