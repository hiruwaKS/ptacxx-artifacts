// <original>

#include <vector>
using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  vector<int*>::iterator it = v.begin();
  int* p = *it;
  return 0;
}
