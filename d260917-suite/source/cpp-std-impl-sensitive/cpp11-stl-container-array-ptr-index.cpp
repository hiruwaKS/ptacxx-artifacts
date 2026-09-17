// <original>

#include <array>

using namespace std;

int main() {
  int a = 1;
  array<int*, 1> arr = {&a};
  int* p = arr[0];
  return 0;
}
