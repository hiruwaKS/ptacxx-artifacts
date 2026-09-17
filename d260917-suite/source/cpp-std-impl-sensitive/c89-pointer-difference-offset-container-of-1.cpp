// <original>

#include <cstddef>

struct S {
  int id;
  char flag;
};

int main() {
  S s;
  s.flag = 0;
  S* p = (S*)((char*)&s.flag - offsetof(S, flag));
  return 0;
}
