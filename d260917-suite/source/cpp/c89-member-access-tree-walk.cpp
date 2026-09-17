// <original>

using namespace std;
struct TNode {
  int v;
  TNode* left;
  TNode* right;
};
int main() {
  int a = 1;
  TNode root{}, left{}, right{};
  root.left = &left;
  root.right = &right;
  TNode* cur = &root;
  while (cur->right)
    cur = cur->right;
  int* p = &cur->v;
  return 0;
}
