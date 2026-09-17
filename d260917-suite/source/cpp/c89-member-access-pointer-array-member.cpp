// <original>

struct Pair {
  int key;
  int* val;
};
struct DenseMap {
  Pair* Buckets;
  unsigned Cap;
};
int main() {
  int a;
  Pair b[4];
  b[1] = {1, &a};
  DenseMap m;
  m.Buckets = b;
  m.Cap = 4;
  int* p = m.Buckets[1].val;
  return 0;
}
