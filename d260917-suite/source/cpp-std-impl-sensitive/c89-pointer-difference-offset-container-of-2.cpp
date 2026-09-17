// <original>

#include <cstddef>
struct S {
  char c;
  int id;
};
int main() {
  S s;
  s.id = 0;
  S* p = (S*)((char*)&s.id - offsetof(S, id));
  return 0;
}
