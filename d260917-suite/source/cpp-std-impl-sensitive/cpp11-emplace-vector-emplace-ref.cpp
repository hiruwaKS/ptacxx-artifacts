// <original>

#include <vector>
using namespace std;
int main() {
  int a = 1;
  vector<int*> v;
  int*& slot = v.emplace_back();
  slot = &a;
  int* p = v[0];
  return 0;
}
