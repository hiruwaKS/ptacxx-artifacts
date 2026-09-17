// <original>

#include <any>
int main() {
  int a;
  std::any an = &a;
  int* p = std::any_cast<int*>(an);
  return 0;
}
