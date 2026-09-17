// <original>

class RefCountedBase {
  unsigned RefCount = 1;

public:
  void retain() {
    ++RefCount;
  }
  void release() {
    if (--RefCount == 0)
      RefCount = 0;
  }
};

template <typename T> class IntrusiveRefCntPtr {
  T* Obj = nullptr;

public:
  explicit IntrusiveRefCntPtr(T* o) : Obj(o) {
    if (o)
      o->retain();
  }
  T* get() const {
    return Obj;
  }
  void reset() {
    Obj = nullptr;
  }
};

struct Node : RefCountedBase {
  int* data;
};

int main() {
  int a = 1;
  Node n;
  n.data = &a;
  IntrusiveRefCntPtr<Node> p(&n);
  IntrusiveRefCntPtr<Node> q(&n);
  Node* p2 = p.get();
  Node* q2 = q.get();
  int* d = p2->data;
  return 0;
}
