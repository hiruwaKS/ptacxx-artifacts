// <original>

using namespace std;
struct Node {
  Node* next;
};
int main() {
  Node n1, n2, n3;
  n1.next = &n2;
  n2.next = &n3;
  n3.next = nullptr;
  Node* temp = &n1;
  Node* found = nullptr;
  while (temp) {
    if (temp == &n3)
      found = temp;
    temp = temp->next;
  }
  return 0;
}
