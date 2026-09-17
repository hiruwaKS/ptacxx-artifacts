// <original>

using namespace std;
struct S {
  int* p;
};
int main() {
  int a = 1;
  S objs[4];
  int* S::*mptr = &S::p;
  for (int i = 0; i < 4; i++)
    objs[i].*mptr = &a;
  int* q = objs[2].p;
  return 0;
}
