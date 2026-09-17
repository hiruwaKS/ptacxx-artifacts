// <original>

using namespace std;
union Value {
  void* ptr;
  unsigned long raw;
};
int main() {
  int a = 1;
  Value v;
  v.ptr = &a;
  void* r = v.ptr;
  return 0;
}
