// <original>

struct S {
  int* p;
};
int main() {
  int a;
  S s;
  int** v = &s.p;
  *v = &a;
  int* q = s.p;
  return 0;
}
