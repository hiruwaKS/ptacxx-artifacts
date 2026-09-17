// <original>

#include <tuple>
using namespace std;
int main() {
  int a = 1;
  tuple<int, int*> t = make_tuple(1, &a);
  int* p = get<1>(t);
  return 0;
}
