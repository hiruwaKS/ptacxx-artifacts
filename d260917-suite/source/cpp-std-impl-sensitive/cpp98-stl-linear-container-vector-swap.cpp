// <original>

#include <vector>
#include <utility>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v(1);
  v[0] = &a;
  vector<int*> w;
  w.swap(v);
  int* p = w[0];
  return 0;
}
