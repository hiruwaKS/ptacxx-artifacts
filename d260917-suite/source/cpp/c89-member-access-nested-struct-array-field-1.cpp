// <original>

struct I {
  int* p;
};
struct O {
  I i[2];
};
int main() {
  int a;
  O o;
  o.i[1].p = &a;
  int* q = o.i[1].p;
  return 0;
}
