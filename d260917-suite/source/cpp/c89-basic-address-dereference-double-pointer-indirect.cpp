// <original>

using namespace std;
int main() {
  int a = 1;
  int* p = nullptr;
  int** out = &p;
  *out = &a;
  return 0;
}
