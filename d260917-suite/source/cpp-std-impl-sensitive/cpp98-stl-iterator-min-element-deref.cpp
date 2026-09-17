// <original>

#include <vector>
#include <algorithm>
using namespace std;
int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  vector<int*>::iterator it = min_element(v.begin(), v.end());
  int* p = *it;
  return 0;
}
