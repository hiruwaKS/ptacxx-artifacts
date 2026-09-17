// <original>

#include <list>
int main() {
  int a;
  std::list<int*> l1, l2;
  l1.push_back(&a);
  l2.splice(l2.begin(), l1);
  int* p = *l2.begin();
  return 0;
}
