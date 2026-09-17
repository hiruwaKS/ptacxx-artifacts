// <original>

#include <cstdarg>
using namespace std;
int* get_ptr(int n, ...) {
  va_list ap;
  va_start(ap, n);
  int* p = va_arg(ap, int*);
  va_end(ap);
  return p;
}
int main() {
  int a = 1;
  int* p = get_ptr(1, &a);
  return 0;
}
