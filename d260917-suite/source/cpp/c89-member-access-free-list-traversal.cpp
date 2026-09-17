// <original>

using namespace std;
struct Block {
  Block* next;
  int v;
};

int main() {

  Block a, b, c;
  a.next = &b;
  b.next = &c;
  c.next = nullptr;
  Block* freeList = &a;

  Block* p = freeList;
  freeList = freeList->next;
  return 0;
}
