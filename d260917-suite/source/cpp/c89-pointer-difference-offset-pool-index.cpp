// <original>

using namespace std;
int main() {
  int a = 1;
  int* pool[4];
  int freeIdx = 0;
  pool[freeIdx++] = &a;
  int idx = 0;
  int* p = pool[idx];
  return 0;
}
