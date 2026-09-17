// <original>

struct N {
  int* v;
};
N* f(int* p, int n) {
  N* r = new N;
  r->v = p;
  if (n == 0)
    return r;
  return f(p, n - 1);
}
int main() {
  int a;
  N* n = f(&a, 2);
  int* q = n->v;
  return 0;
}
