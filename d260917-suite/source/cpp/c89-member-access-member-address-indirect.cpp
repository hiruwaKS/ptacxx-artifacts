// <original>

using namespace std;
struct Slot {
  int* ptr;
};
int main() {
  int a = 1;
  Slot s;
  int** ref = &s.ptr;
  *ref = &a;
  int* p = s.ptr;
  return 0;
}
