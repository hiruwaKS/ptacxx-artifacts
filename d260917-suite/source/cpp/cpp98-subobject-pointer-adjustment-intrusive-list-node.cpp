// <original>

struct ilist_node {
  ilist_node* Prev = nullptr;
  ilist_node* Next = nullptr;
};
struct Obj : ilist_node {
  int val;
};

struct List {
  Obj* Head = nullptr;
  Obj* Tail = nullptr;
  void push_back(Obj* o) {
    o->Prev = Tail;
    o->Next = nullptr;
    if (Tail)
      Tail->Next = o;
    else
      Head = o;
    Tail = o;
  }
  Obj* front() {
    return Head;
  }
};

int main() {
  int a = 1;
  Obj o1, o2;
  o1.val = a;
  o2.val = a;
  List l;
  l.push_back(&o1);
  l.push_back(&o2);
  Obj* p = l.front();
  return 0;
}
