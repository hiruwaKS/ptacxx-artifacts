// <original>

using namespace std;
int main() {
  int a = 1;
  int*** p3;
  int** p2;
  int* p1 = &a;
  p2 = &p1;
  p3 = &p2;
  int* r = **p3;
  return 0;
}
