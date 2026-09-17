// <original>

#include <variant>
#include <functional>
void a() {
}
int main() {
  std::variant<std::function<void()>> v;
  v = std::function<void()>(a);
  std::get<0>(v)();
  return 0;
}
