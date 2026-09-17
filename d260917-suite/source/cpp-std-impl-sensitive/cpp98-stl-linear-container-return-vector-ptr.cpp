// <original>

#include <vector>

using namespace std;

vector<int*> make_vec(int* x) {
  vector<int*> v;
  v.push_back(x);
  return v;
}

int main() {
  int a = 1;
  vector<int*> v = make_vec(&a);
  int* p = v[0];
  return 0;
}
