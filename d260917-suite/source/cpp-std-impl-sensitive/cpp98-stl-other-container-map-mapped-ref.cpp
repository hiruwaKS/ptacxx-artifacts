// <original>

#include <map>

using namespace std;

int main() {
  int a = 1;
  map<int, int*> m;
  int*& r = m[1];
  r = &a;
  int* p = m[1];
  return 0;
}
