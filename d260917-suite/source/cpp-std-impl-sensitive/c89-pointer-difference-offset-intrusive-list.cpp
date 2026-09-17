// <original>

#include <cstddef>
using namespace std;
struct ListHead {
  ListHead* next;
};
struct Var {
  int id;
  ListHead list;
  int* val;
};
int main() {
  int a = 1;
  Var v1, v2;
  v1.list.next = &v2.list;
  v2.list.next = nullptr;
  v1.val = &a;

  ListHead* pos = &v1.list;
  Var* cur = (Var*)((char*)pos - offsetof(Var, list));
  int* p = cur->val;
  return 0;
}
