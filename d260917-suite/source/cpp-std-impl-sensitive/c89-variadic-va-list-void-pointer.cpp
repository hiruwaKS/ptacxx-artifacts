// <original>

#include <cstdarg>

using namespace std;

void* get_ptr(int n, ...) {
  va_list ap;
  va_start(ap, n);
  void* p = va_arg(ap, void*);
  va_end(ap);
  return p;
}

int main() {
  int a = 1;
  void* p = get_ptr(1, &a);
  return 0;
}
