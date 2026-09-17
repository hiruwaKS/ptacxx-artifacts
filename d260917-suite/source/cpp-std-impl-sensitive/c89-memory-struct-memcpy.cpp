// <original>

#include <cstring>
struct S {
  int* p;
};
int main() {
  int a;
  S s;
  s.p = &a;
  S t;
  std::memcpy(&t, &s, sizeof(S));
  int* q = t.p;
  return 0;
}
