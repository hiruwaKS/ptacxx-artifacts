// <original>

struct S {
  int* p;
};
S garr[4];
int main() {
  int a;
  int i = 2;
  garr[i].p = &a;
  int* q = garr[i].p;
  return 0;
}
