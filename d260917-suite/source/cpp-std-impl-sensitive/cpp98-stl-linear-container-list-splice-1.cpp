// <original>

#include <list>

using namespace std;

int main() {
  int a = 1;
  list<int*> l;
  l.push_back(&a);
  l.push_back(&a);
  list<int*> m;
  m.splice(m.begin(), l);
  int* p = m.front();
  return 0;
}
