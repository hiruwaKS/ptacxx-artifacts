// <original>

struct N {
  N* next;
  int* v;
};
int main() {
  int a, b;
  N n1, n2;
  n1.next = &n2;
  n1.v = &b;
  n2.next = 0;
  n2.v = &a;
  N* cur = &n1;
  while (cur) {
    cur = cur->next;
  }
  int* p = &a;
  return 0;
}
