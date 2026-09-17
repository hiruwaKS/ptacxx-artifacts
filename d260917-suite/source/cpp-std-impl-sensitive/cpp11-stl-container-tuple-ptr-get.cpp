// <original>

#include <vector>
#include <tuple>

using namespace std;

int main() {
  int a = 1;
  vector<tuple<int, int*>> v;
  v.push_back(make_tuple(1, &a));
  int* p = get<1>(v[0]);
  return 0;
}
