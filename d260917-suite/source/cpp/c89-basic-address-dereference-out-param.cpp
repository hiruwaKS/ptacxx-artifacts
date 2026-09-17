// <original>

void fill(int** out, int* x) {
  *out = x;
}
int main() {
  int a;
  int* p = 0;
  fill(&p, &a);
  return 0;
}
