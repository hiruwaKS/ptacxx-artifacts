// <original>

#include <vector>
#include <functional>

using namespace std;

int main() {
  int a = 1;
  int* q = &a;
  reference_wrapper<int*> rw(q);
  vector<int*> v;
  v.push_back(rw);
  int* p = v[0];
  return 0;
}
