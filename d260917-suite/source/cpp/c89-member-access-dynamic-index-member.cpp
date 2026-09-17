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
  Pair b[4];
  b[2] = {1, &a};
  DenseMap m;
  m.Buckets = b;
  int i = 2;
  int* p = m.Buckets[i].val;
  return 0;
}
