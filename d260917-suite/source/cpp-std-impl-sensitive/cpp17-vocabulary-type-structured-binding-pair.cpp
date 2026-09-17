// <original>

#include <utility>
using namespace std;
int main() {
  int a = 1;
  pair<int, int*> pr(1, &a);
  auto [k, p] = pr;
  return 0;
}
