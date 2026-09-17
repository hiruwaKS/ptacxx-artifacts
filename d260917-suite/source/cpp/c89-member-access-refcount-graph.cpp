// <original>

using namespace std;
struct IRNode {
  int ref;
  IRNode* a;
  IRNode* b;
};
IRNode* retain(IRNode* n) {
  n->ref++;
  return n;
}
int main() {
  int x = 1;
  IRNode n1, n2;
  n1.ref = 1;
  n1.a = &n2;
  n1.b = nullptr;
  n2.ref = 1;
  n2.a = nullptr;
  n2.b = nullptr;
  IRNode* r = retain(&n1);
  IRNode* op = r->a;
  return 0;
}
