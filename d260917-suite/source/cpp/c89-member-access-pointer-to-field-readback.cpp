// <original>

using namespace std;
struct S {
  int* p;
  int v;
};
int main() {
  int a = 1;
  int* S::*mptr = &S::p;
  S obj;
  obj.*mptr = &a;
  int* q = obj.*mptr;
  return 0;
}
