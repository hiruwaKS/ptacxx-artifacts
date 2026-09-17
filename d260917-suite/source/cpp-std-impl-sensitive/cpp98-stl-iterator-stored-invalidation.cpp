// <original>

#include <vector>
#include <functional>

using namespace std;

int main() {
  int a = 1;
  vector<int*> v;
  v.push_back(&a);
  vector<int*>::iterator it = v.begin();
  v.push_back(&a);
  int* p = *it;
  return 0;
}
