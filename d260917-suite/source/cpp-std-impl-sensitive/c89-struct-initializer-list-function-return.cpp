// <original>

#include <utility>
using namespace std;
struct S {
  int* q;
};
S makeS(int* x) {
  return S{x};
}
int main() {
  int a = 1;
  S s = makeS(&a);
  int* p = s.q;
  return 0;
}
