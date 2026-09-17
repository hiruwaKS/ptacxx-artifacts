// <original>

#include <vector>
#include <functional>
void a() {
}
int main() {
  std::vector<std::function<void()>> v;
  v.push_back(std::function<void()>(a));
  v[0]();
  return 0;
}
