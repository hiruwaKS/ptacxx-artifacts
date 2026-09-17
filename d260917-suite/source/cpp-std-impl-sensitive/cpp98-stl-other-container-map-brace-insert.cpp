// <original>

#include <map>
using namespace std;

int main() {
  int a = 1;
  map<int, int*> m;
  m.insert({1, &a});
  int* p = m[1];
  return 0;
}
