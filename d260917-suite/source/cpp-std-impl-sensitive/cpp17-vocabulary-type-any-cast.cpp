// <original>

#include <any>
struct S {
  int* p;
};
int main() {
  int a;
  S s;
  s.p = &a;
  std::any an = &s;
  S* q = std::any_cast<S*>(an);
  int* r = q->p;
  return 0;
}
