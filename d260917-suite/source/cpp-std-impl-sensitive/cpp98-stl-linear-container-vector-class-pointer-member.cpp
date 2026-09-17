// <original>

#include <vector>
using namespace std;
class C {
public:
  int* q;
  C(int* x) : q(x) {
  }
};
int main() {
  int a = 1;
  C c(&a);
  vector<C> v;
  v.push_back(c);
  int* p = v[0].q;
  return 0;
}
