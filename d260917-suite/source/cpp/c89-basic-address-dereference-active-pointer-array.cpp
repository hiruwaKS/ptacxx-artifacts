// <original>

using namespace std;
int main() {
  int a = 1;
  int* bufA[4];
  int* bufB[4];
  int** active = bufA;
  active[0] = &a;
  active = bufB;
  active[0] = &a;
  active = bufA;
  int* p = active[0];
  return 0;
}
