// <original>

#include <cstring>
using namespace std;
struct S {
  int* q;
};
int main() {
  int a = 1;
  S s1;
  s1.q = &a;
  S s2;
  memcpy(&s2, &s1, sizeof(S));
  int* p = s2.q;
  return 0;
}
