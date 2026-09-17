// <original>

struct S {
  int* arr[4];
};
int main() {
  int a;
  S s;
  int i = 2;
  s.arr[i] = &a;
  int* q = s.arr[i];
  return 0;
}
