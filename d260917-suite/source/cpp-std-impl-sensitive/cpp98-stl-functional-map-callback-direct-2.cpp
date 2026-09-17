// <original>

#include <functional>
#include <map>
using namespace std;
void target() {
}
void middle(function<void()> cb) {
  cb();
}
int main() {
  map<int, function<void()>> callbacks = {{1, target}};
  middle(callbacks[1]);
  return 0;
}
