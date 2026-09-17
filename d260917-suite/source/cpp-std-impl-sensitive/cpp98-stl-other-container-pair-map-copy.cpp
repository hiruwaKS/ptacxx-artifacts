// <original>

#include <map>
#include <utility>
using namespace std;
int main() {
  int a = 1;
  pair<int, int*> p(1, &a);
  map<int, int*> m;
  m.insert(p);
  int* p2 = m[1];
  return 0;
}
