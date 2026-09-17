// <original>

struct N {
  N* next;
  void (*f)();
};
void h() {
}
int main() {
  N n;
  n.next = 0;
  n.f = h;
  N* cur = &n;
  while (cur) {
    cur->f();
    cur = cur->next;
  }
  return 0;
}
