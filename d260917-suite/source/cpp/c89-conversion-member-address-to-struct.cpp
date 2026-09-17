// <original>

struct S {
  int x;
  int y;
};
int main() {
  S s;
  S* ps = (S*)(&s.y);
  return 0;
}
