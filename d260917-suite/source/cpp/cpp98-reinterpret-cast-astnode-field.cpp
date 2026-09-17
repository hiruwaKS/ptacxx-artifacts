// <original>

using namespace std;
struct ASTNode {
  int tag;
};
struct ExprNode {
  int tag;
  int* val;
};
struct Visitor {
  void (*visit_expr)(ExprNode*);
};
void do_visit(ExprNode* e) {
  e->val = nullptr;
}
int main() {
  int a = 1;
  ExprNode e;
  e.val = &a;
  ASTNode* self = (ASTNode*)&e;
  ExprNode* expr = (ExprNode*)self;
  int* p = expr->val;
  return 0;
}
