// <original>

#include <vector>
using namespace std;
int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  int** d = v.data();
  int* p = *d;
  return 0;
}
