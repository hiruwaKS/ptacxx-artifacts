// <original>

using namespace std;
struct IRNode {
  int ref;
  IRNode* operand;
};
IRNode* retain(IRNode* n) {
  n->ref++;
  return n;
}
int main() {
  int a = 1;
  IRNode node;
  node.operand = nullptr;
  IRNode* r = retain(&node);
  return 0;
}
