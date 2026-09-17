// <original>

#include <map>
int main() {
  int a;
  std::map<int, int*> m;
  m.insert({1, &a});
  int k = 1;
  int* p = m[k];
  return 0;
}
