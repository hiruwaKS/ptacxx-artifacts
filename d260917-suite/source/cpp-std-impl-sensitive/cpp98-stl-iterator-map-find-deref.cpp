// <original>

#include <map>
using namespace std;
int main() {
  int a = 1;
  map<int, int*> m;
  m[1] = &a;
  map<int, int*>::iterator it = m.find(1);
  int* p = it->second;
  return 0;
}
