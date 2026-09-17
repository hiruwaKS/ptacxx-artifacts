// <original>

using namespace std;
struct Node {
  int* val;
  Node* next;
};
class List {
  Node head_;

public:
  Node* begin() {
    return &head_;
  }
};
int main() {
  int a = 1;
  List lst;
  Node* it = lst.begin();
  it->val = &a;
  Node* it2 = lst.begin();
  int* p = it2->val;
  return 0;
}
