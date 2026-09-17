// <original>

#include <forward_list>

using namespace std;

int main() {
  int a = 1;
  forward_list<int*> l;
  l.push_front(&a);
  int* p = l.front();
  return 0;
}
