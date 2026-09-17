// <original>

int g;
int* f1() {
  return &g;
}
int* f2() {
  int* p = f1();
  return p;
}
int main() {
  int* p = f2();
  return 0;
}
