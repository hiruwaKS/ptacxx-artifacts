// <original>

struct node {
  node* prev;
  node* next;
};
struct Obj : node {
  int* data;
};
struct List {
  Obj* head;
};
int main() {
  int a;
  Obj o;
  o.data = &a;
  List l1, l2;
  l1.head = &o;
  l2.head = &o;
  Obj* p = l2.head;
  return 0;
}
