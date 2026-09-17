// <original>

#include <map>
#include <utility>
using namespace std;
int main() {
  int a = 1;
  map<int, int*> m;
  pair<map<int, int*>::iterator, bool> r = m.insert({1, &a});
  map<int, int*>::iterator it = r.first;
  int* p = it->second;
  return 0;
}
