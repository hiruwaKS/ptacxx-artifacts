// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  vector<int*> w = move(v);
  int* p = w[0];
  return 0;
}
