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
  while (cur) {
    cur = cur->next;
  }
  int* p = &a;
  return 0;
}
