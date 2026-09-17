// <original>

int* gp;
void set(int* x) {
  gp = x;
}
int main() {
  int a;
  set(&a);
  int* p = gp;
  return 0;
}
