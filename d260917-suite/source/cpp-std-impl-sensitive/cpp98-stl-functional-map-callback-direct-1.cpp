// <original>

#include <functional>
#include <map>

using namespace std;

void target() {
}

int main() {
  std::map<int, std::function<void()>> callbacks = {{1, target}};
  callbacks[1]();
  return 0;
}
