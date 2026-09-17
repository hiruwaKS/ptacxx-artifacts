// <original>

using namespace std;
int main() {
  int a = 1;
  int* A[4][4];
  int r = 2, c = 3;
  A[r][c] = &a;
  int* p = A[r][c];
  return 0;
}
