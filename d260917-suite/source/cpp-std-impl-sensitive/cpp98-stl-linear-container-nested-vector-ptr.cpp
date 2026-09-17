// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<vector<int*>> vv;
  vv.resize(1);
  vv[0].push_back(&a);
  int* p = vv[0][0];
  return 0;
}
