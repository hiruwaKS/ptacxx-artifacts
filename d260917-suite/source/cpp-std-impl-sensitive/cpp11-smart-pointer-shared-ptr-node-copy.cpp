// <original>

#include <memory>
struct Node {
  std::shared_ptr<Node> next;
  int* v;
};
int main() {
  int a = 1;
  auto n = std::make_shared<Node>();
  n->v = &a;
  auto m = n;
  std::shared_ptr<Node> k;
  k = m;
  int* p = k->v;
  return 0;
}
