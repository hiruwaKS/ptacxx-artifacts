// <original>

using namespace std;
struct S {
  int* ptr;
};
int main() {
  int a = 1;
  char buf[sizeof(S)];
  S* s = reinterpret_cast<S*>(buf);
  s->ptr = &a;
  int* r = s->ptr;
  return 0;
}
