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
  int* p = &a;
  return 0;
}
