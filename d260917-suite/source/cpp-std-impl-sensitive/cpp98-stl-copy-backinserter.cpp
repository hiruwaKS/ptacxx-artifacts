// <original>

#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  vector<int*> w;
  copy(v.begin(), v.end(), back_inserter(w));
  int* p = w[0];
  return 0;
}
