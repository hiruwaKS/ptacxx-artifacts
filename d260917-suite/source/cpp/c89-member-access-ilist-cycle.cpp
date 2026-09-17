// <original>

struct ilist_node {
  ilist_node* Prev;
  ilist_node* Next;
};
struct Obj : ilist_node {
  int* v;
};
int main() {
  int a;
  Obj o1, o2;
  o1.v = &a;
  o1.Next = &o2;
  o2.Prev = &o1;
  o2.Next = &o1;
  o1.Prev = &o2;
  Obj* p = &o1;
  return 0;
}
