// <original>

#include <vector>
#include <algorithm>
using namespace std;
int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  vector<int*>::iterator it = find(v.begin(), v.end(), &a);
  int* p = *it;
  return 0;
}
