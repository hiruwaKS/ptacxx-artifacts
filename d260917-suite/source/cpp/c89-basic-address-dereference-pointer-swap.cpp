// <original>

using namespace std;
int main() {
  int a = 1, b = 2;
  int* x = &a;
  int* y = &b;
  int* tmp = x;
  x = y;
  y = tmp;
  return 0;
}
