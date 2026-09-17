// <original>

#include <optional>

using namespace std;

int main() {
  int a = 1;
  optional<int*> o = &a;
  int* p = *o;
  return 0;
}
