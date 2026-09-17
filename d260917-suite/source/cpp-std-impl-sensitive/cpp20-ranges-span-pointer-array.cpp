// <original>

#include <span>
using namespace std;
int main() {
  int a = 1;
  int* arr[2];
  arr[0] = &a;
  span<int*> s(arr, 2);
  int* p = s[0];
  return 0;
}
