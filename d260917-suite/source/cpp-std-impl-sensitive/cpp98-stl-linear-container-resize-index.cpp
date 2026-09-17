// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.resize(1);
  v[0] = &a;
  int* p = v[0];
  return 0;
}
