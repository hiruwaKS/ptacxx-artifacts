// <original>

#include <deque>

using namespace std;

int main() {
  int a = 1;
  deque<int*> d;
  d.push_front(&a);
  int* p = d.front();
  return 0;
}
