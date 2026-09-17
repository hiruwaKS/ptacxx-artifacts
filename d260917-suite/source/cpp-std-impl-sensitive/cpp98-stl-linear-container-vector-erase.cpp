// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  v.push_back(&a);
  v.erase(v.begin());
  int* p = v[0];
  return 0;
}
