// <original>

#include <variant>
using namespace std;
int main() {
  int a = 1;
  variant<int*, int> v = &a;
  int* p = get<int*>(v);
  return 0;
}
