// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v(1);
  v[0] = &a;
  vector<int*> w;
  w = v;
  int* p = w[0];
  return 0;
}
