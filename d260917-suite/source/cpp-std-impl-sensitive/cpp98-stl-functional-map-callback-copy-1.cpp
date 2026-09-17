// <original>

#include <functional>
#include <map>

using namespace std;

void target() {
}

void middleFunction(std::function<void()> cb) {
  cb();
}

int main() {
  std::map<int, std::function<void()>> callbacks = {{1, target}};
  middleFunction(callbacks[1]);
  return 0;
}
