// <original>

struct S {
  int* p;
};
int main() {
  int a;
  S* s = new S;
  s->p = &a;
  int* q = s->p;
  return 0;
}
