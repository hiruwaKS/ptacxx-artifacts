// <original>

using namespace std;
struct S {
  int* p;
  int* q;
};
int main() {
  int a = 1, b = 2;
  int* S::*m = &S::p;
  int* S::*m2 = &S::q;
  S obj;
  obj.*m = &a;
  obj.*m2 = &b;
  int* r = obj.p;
  return 0;
}
