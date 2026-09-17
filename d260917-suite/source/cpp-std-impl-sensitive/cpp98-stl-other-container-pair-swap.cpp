// <original>

#include <utility>
using namespace std;
int main() {
  int a = 1, b = 2;
  pair<int*, int*> x(&a, &b);
  pair<int*, int*> y(&b, &a);
  swap(x, y);
  int* p = x.first;
  return 0;
}
