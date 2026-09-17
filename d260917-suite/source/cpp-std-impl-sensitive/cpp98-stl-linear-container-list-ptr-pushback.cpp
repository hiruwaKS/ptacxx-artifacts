// <original>

#include <list>
using namespace std;

int main() {
  int a = 1;
  list<int*> l;
  l.push_back(&a);
  int* p = l.front();
  return 0;
}
