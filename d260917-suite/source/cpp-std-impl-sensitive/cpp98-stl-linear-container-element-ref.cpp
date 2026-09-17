// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v(1);
  int*& r = v[0];
  r = &a;
  int* p = v[0];
  return 0;
}
