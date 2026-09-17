// <original>

using namespace std;
union V {
  void* p;
  double d;
};
int main() {
  int a = 1;
  V v;
  v.p = &a;
  void* r = v.p;
  return 0;
}
