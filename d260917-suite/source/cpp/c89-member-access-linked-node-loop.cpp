// <original>

struct N {
  N* next;
  int* v;
};
int main() {
  int a;
  N n;
  n.next = 0;
  n.v = &a;
  N* cur = &n;
  for (int i = 0; i < 2 && cur; i++) {
    cur = n.next;
  }
  int* p = &a;
  return 0;
}
