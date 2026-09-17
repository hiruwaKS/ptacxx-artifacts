// <original>

struct Exp {
  int* p;
  int err;
};
Exp mk(int* x) {
  return {x, 0};
}
int main() {
  int a;
  Exp e = mk(&a);
  int* p = e.p;
  return 0;
}
