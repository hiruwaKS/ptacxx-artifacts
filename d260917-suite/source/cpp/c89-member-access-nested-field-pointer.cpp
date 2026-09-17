// <original>

struct Pair {
  int key;
  int* val;
};
struct DenseMap {
  Pair* Buckets;
};
int main() {
  int a;
  Pair b;
  b.val = &a;
  DenseMap m;
  m.Buckets = &b;
  int* p = m.Buckets->val;
  return 0;
}
