// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  v.insert(v.begin(), &a);
  int* p = v[0];
  return 0;
}
