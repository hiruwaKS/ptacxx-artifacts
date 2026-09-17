// <original>

struct Pair {
  int key;
  int* val;
};
int main() {
  int a;
  Pair b[4];
  b[1] = {1, &a};
  int* p = b[1].val;
  return 0;
}
