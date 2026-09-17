// <original>

#include <set>

using namespace std;

int main() {
  int a = 1;
  set<int*> s;
  s.insert(&a);
  int* p = *s.begin();
  return 0;
}
