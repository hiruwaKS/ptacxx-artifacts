// <original>

using namespace std;
int main() {
  int a = 1, b = 2;
  int *bufA[2], *bufB[2];
  int toggle = 0;
  if (toggle) {
    bufA[0] = &a;
  } else {
    bufB[0] = &a;
  }
  int* p = bufB[0];
  return 0;
}
