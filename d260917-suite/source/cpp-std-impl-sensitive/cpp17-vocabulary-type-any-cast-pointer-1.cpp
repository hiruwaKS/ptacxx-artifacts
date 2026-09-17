// <original>

#include <any>
using namespace std;
int main() {
  int a = 1;
  any o = &a;
  int* p = any_cast<int*>(o);
  return 0;
}
