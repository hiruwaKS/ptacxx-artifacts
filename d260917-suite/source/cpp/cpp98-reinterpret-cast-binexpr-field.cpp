// <original>

using namespace std;
struct ASTNode {
  int tag;
};
struct BinExpr {
  int tag;
  int* lhs;
  int* rhs;
};
int main() {
  int a = 1, b = 2;
  BinExpr e;
  e.lhs = &a;
  ASTNode* self = (ASTNode*)&e;
  BinExpr* expr = (BinExpr*)self;
  int* p = expr->lhs;
  return 0;
}
