// <original>

struct S {
  int x;
  int y;
};
int main() {
  S s;
  int* py = &s.y;
  int* px = py - 1;
  S* ps = (S*)px;
  return 0;
}
