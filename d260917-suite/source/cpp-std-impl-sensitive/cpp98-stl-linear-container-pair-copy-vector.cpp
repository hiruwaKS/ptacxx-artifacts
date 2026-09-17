// <original>

#include <vector>
#include <utility>
using namespace std;
int main() {
  int a = 1;
  pair<int, int*> p(1, &a);
  vector<pair<int, int*>> v;
  v.push_back(p);
  int* p2 = v[0].second;
  return 0;
}
