// <original>

using namespace std;
int main() {
  int a = 1;
  void* v = (void*)&a;
  int* p = (int*)v;
  return 0;
}
