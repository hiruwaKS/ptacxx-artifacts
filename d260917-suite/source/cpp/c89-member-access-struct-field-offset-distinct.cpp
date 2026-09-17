// <original>

using namespace std;
struct S {
  int* p;
  int* q;
};
int main() {
  int a = 1;
  S s;
  s.p = &a;
  int* x = s.q;
  return 0;
}
