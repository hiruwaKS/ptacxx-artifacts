// <original>

struct S {
  int* p;
};
int main() {
  int a;
  S arr[4];
  int i = 2;
  arr[i].p = &a;
  int* q = arr[i].p;
  return 0;
}
