// <original>

#include <vector>
int main() {
  int a;
  std::vector<int*> v;
  v.push_back(&a);
  int* p = v[0];
  return 0;
}
