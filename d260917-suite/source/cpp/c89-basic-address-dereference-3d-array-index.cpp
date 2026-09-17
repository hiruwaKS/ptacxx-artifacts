// <original>

int main() {
  int a;
  int* M[2][2][2];
  int i = 1;
  M[i][1][0] = &a;
  int* p = M[i][1][0];
  return 0;
}
