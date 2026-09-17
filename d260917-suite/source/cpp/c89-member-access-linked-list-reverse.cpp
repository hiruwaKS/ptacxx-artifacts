// <original>

using namespace std;
struct Node {
  int v;
  Node* next;
};
int main() {
  Node a, b, c;
  a.next = &b;
  b.next = &c;
  c.next = nullptr;

  Node* prev = nullptr;
  Node* cur = &a;
  while (cur) {
    Node* nxt = cur->next;
    cur->next = prev;
    prev = cur;
    cur = nxt;
  }
  Node* head = prev;
  return 0;
}
