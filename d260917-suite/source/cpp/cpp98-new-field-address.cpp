// <original>

struct S {
  int x;
  int y;
};
int main() {
  S* s = new S;
  int* p = &s->x;
  return 0;
}
