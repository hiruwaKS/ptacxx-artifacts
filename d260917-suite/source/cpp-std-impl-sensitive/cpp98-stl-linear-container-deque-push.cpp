// <original>

#include <deque>
int main() {
  int a;
  std::deque<int*> d;
  d.push_back(&a);
  int* p = d[0];
  return 0;
}
