// <original>

#include <map>

using namespace std;

int main() {
  int a = 1;
  int* p = &a;
  map<int, int*> m;
  m.insert(make_pair(1, p));
  return 0;
}
