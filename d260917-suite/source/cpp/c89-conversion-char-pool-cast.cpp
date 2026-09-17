// <original>

using namespace std;
struct Pool {
  int* data;
};
int main() {
  int a = 1;
  char pool[128];
  Pool* node = (Pool*)((char*)pool + 8);
  node->data = &a;
  Pool* cur = (Pool*)((char*)pool + 8);
  int* p = cur->data;
  return 0;
}
