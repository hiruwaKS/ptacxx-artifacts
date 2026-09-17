// <original>

#include <vector>
using namespace std;
int main() {
  int a = 1;
  vector<int*> v(2);
  v[0] = &a;
  int i = 1;
  int* p = v[i];
  return 0;
}
