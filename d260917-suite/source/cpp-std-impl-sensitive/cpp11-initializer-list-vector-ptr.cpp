// <original>

#include <vector>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v = {&a};
  int* p = v[0];
  return 0;
}
