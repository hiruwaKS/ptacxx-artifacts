// <original>

using namespace std;
struct Node {
  int size;
  int* val;
};
int main() {
  int a = 1;
  char pool[256];
  Node* n0 = (Node*)((char*)pool + 0);
  Node* n1 = (Node*)((char*)pool + 16);
  n0->val = &a;
  n1->val = &a;
  Node* cur = (Node*)((char*)pool + 16);
  int* p = cur->val;
  return 0;
}
