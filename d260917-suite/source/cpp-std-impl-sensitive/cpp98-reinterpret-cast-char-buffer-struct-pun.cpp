// <original>

#include <cstring>
struct S {
  void (*f)();
};
void a() {
}
int main() {
  char buf[64];
  S* s = (S*)buf;
  s->f = a;
  s->f();
  return 0;
}
