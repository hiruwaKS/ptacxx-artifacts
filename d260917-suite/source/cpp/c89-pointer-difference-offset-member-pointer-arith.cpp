// <original>

struct S {
  int x;
  int y;
};
int main() {
  S s;
  int* py = &s.y;
  S* ps = (S*)(py - 2);
  return 0;
}
